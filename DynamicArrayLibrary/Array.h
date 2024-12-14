#include <assert.h>
#include <memory>


template <typename T>
class Array {
private:
    T* data;
    int capacity;
    int count;

    void resize(int newCapacity) {
        T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
        assert(newData);

        for (int i = 0; i < count; ++i) {
            new (newData + i) T(std::move(data[i]));
            data[i].~T();
        }

        free(data);
        data = newData;
        capacity = newCapacity;
    }

public:
    Array() : Array(16) {}
    Array(int initialCapacity) : data(nullptr), capacity(initialCapacity), count(0) {
        data = static_cast<T*>(malloc(capacity * sizeof(T)));
        assert(data);
    }

    ~Array() {
        for (int i = 0; i < count; ++i) {
            data[i].~T();
        }
        free(data);
    }

    Array(const Array& other) : data(nullptr), capacity(other.capacity), count(other.count) {
        data = static_cast<T*>(malloc(capacity * sizeof(T)));
        assert(data);

        for (int i = 0; i < count; ++i) {
            new (data + i) T(other.data[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        for (int i = 0; i < count; ++i) {
            data[i].~T();
        }
        free(data);

        capacity = other.capacity;
        count = other.count;
        data = static_cast<T*>(malloc(capacity * sizeof(T)));
        assert(data);

        for (int i = 0; i < count; ++i) {
            new (data + i) T(other.data[i]);
        }

        return *this;
    }

    int insert(const T& value) {
        if (count == capacity) {
            resize(capacity * 2);
        }
        new (data + count) T(value);
        return count++;
    }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= count);

        if (count == capacity) {
            resize(capacity * 2);
        }

        for (int i = count; i > index; --i) {
            new (data + i) T(std::move(data[i - 1]));
            data[i - 1].~T();
        }

        new (data + index) T(value);
        ++count;
        return index;
    }

    void remove(int index) {
        assert(index >= 0 && index < count);

        data[index].~T();
        for (int i = index; i < count - 1; ++i) {
            new (data + i) T(std::move(data[i + 1]));
            data[i + 1].~T();
        }
        --count;
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < count);
        return data[index];
    }

    T& operator[](int index) {
        assert(index >= 0 && index < count);
        return data[index];
    }

    int size() const {
        return count;
    }

    T* begin() { return data; }
    T* end() { return data + count; }


    class Iterator {
    private:
        T* current;
        T* end;

    public:
        Iterator(T* start, T* end) : current(start), end(end) {}

        const T& get() const {
            assert(current < end);
            return *current;
        }

        void set(const T& value) {
            assert(current < end);
            *current = value;
        }

        void next() {
            assert(current < end);
            ++current;
        }

        bool hasNext() const {
            return current < end;
        }
    };

    class ReverseIterator {
    private:
        T* current;
        T* start;

    public:
        ReverseIterator(T* start, T* end) : current(end - 1), start(start) {}

        const T& get() const {
            assert(current >= start);
            return *current;
        }

        void set(const T& value) {
            assert(current >= start);
            *current = value;
        }

        void next() {
            assert(current >= start);
            --current;
        }

        bool hasNext() const {
            return current >= start;
        }
    };

    Iterator iterator() {
        return Iterator(data, data + count);
    }

    ReverseIterator reverseIterator() {
        return ReverseIterator(data, data + count);
    }
};