#include <assert.h>
#include <memory>
#include <cstdlib>
#include <utility>


template <typename T>
class Array {
private:
    T* _data;
    int _capacity;
    int _size;

    void resize(int newCapacity) {
        T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
        if (!newData) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < _size; ++i) {
            new (newData + i) T(std::move(_data[i]));
            _data[i].~T();
        }
        free(_data);
        _data = newData;
        _capacity = newCapacity;
    }

public:
    Array() : Array(16) {}

    ~Array() {
        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);
        _size = 0;
    }

    Array(int newSize) : _capacity(newSize), _size(0)
    {
        _data = static_cast<T*>(malloc(_capacity * sizeof(T)));

        if (!_data) {
            throw std::bad_alloc();
        }
    }


    Array(const Array& other) : _capacity(other._capacity), _size(other._size) {
        _data = static_cast<T*>(malloc(_capacity * sizeof(T)));
        if (!_data) {
            throw std::bad_alloc();
        }

        for (int i = 0; i < _size; ++i) {
            new (_data + i) T(other._data[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);

        _capacity = other._capacity;
        _size = other._size;
        _data = static_cast<T*>(malloc(_capacity * sizeof(T)));
        assert(_data);

        for (int i = 0; i < _size; ++i) {
            new (_data + i) T(other._data[i]);
        }

        return *this;
    }

    int insert(const T& value) {
        return insert(_size, value);
    }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= _size);

        if (_size == _capacity) {
            resize(_capacity * 2);
        }
        for (int i = _size; i > index; --i) {
            if (std::is_move_constructible_v<T>) {
                new (_data + i) T(std::move(_data[i - 1]));
            }
            else {
                new (_data + i) T(_data[i - 1]);
                _data[i - 1].~T();
            }
        }

        new (_data + index) T(value);
        ++_size;
        return index;
    }

    void remove(int index) {
        assert(index >= 0 && index < _size);

        _data[index].~T();

        if constexpr (std::is_move_constructible_v<T>) {
            for (int i = index; i < _size - 1; ++i) {
                new (_data + i) T(std::move(_data[i + 1]));
                _data[i + 1].~T();
            }
        }
        else {
            for (int i = index; i < _size - 1; ++i) {
                new (_data + i) T(_data[i - 1]);
                _data[i - 1].~T();
            }
        }
        
        _size--;
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < _size);
        return _data[index];
    }

    T& operator[](int index) {
        assert(index >= 0 && index < _size);
        return _data[index];
    }

    int size() const {
        return _size;
    }

    T* begin() { return _data; }
    T* end() { return _data + _size; }


    class Iterator {
    private:
        T* _current;
        T* _end;

    public:
        Iterator(T* _start, T* _end) : _current(_start), _end(_end) {}

        const T& get() const {
            assert(_current < _end);
            return *_current;
        }

        void set(const T& value) {
            assert(_current < _end);
            *_current = value;
        }

        void next() {
            assert(_current < _end);
            ++_current;
        }

        bool hasNext() const {
            return _current < _end;
        }
    };

    class ReverseIterator {
    private:
        T* _current;
        T* _start;

    public:
        ReverseIterator(T* _start, T* _end) : _current(_end - 1), _start(_start) {}

        const T& get() const {
            assert(_current >= _start);
            return *_current;
        }

        void set(const T& value) {
            assert(_current >= _start);
            *_current = value;
        }

        void next() {
            assert(_current >= _start);
            --_current;
        }

        bool hasNext() const {
            return _current >= _start;
        }
    };

    Iterator iterator() {
        return Iterator(_data, _data + _size);
    }

    ReverseIterator reverseIterator() {
        return ReverseIterator(_data, _data + _size);
    }
};