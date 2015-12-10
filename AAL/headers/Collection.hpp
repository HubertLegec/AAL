#ifndef COLLECTION
#define COLLECTION

#include <vector>
#include <algorithm>

template<typename T>
class Collection {
private:
	std::vector<T> collection;

public:
	class const_iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	protected:
		friend class Collection<T>;
		std::vector<T>& vec = nullptr;
		int counter;

		const_iterator(std::vector<T>& vector, int counter) : vec(vector), counter(counter) {}
	public:

		//--------------------------------- ITERATORS ---------------------------------------------------
		const_iterator() {}
		const_iterator(const const_iterator& other) : vec(other.vec), counter(other.counter) {}
		inline const T& operator*() const
		{
			return this->vec[counter];
		}

		inline const T* operator->() const
		{
			return &(this->vec[counter]);
		}

		inline bool operator==(const const_iterator& a) const
		{
			return this->vec == a.vec && this->counter == a.counter;
		}

		inline bool operator!=(const const_iterator& a) const
		{
			return this->vec != a.vec || this->counter != a.counter;
		}

		// preincrement
		const_iterator& operator++() {
			if(this->counter < this->vec.size())
				this->counter++; //(counter + 1) % vec.size();
			return *this;
		}
		// postincrement
		const_iterator operator++(int) {
			const_iterator result(*this);
			++(*this);
			return result;
		}
		// predecrement
		const_iterator& operator--() {
			this->counter = this->counter > 0 ? (this->counter - 1) : this->counter; //(vec.size() - 1);
			return *this;
		}
		// postdecrement
		const_iterator operator--(int) {
			const_iterator result(*this);
			--(*this);
			return result;
		}
	};

	class iterator : public const_iterator
	{
		friend class Collection<T>;

		iterator(std::vector<T>& vector, int counter) : const_iterator(vector, counter) {}
	public:
		iterator() {}
		iterator(const const_iterator& a) : const_iterator(a) {}
		iterator(const iterator& a) : const_iterator(a) {

		}

		inline T& operator*() const
		{
			return this->vec[this->counter];
		}
		inline T* operator->() const
		{
			return &(this->vec[this->counter]);
		}

		iterator& operator++()
		{  // preincrementacja
			++(*(const_iterator*)this);
			return (*this);
		}

		iterator operator++(int)
		{  // postincrementacja
			iterator temp = *this;
			++*this;
			return temp;
		}

		iterator& operator--()
		{  // predekrementacja
			--(*(const_iterator*)this);
			return (*this);
		}

		iterator operator--(int)
		{  // postdekrementacja
			iterator temp = *this;
			--*this;
			return temp;
		}
	};
	//-----------------------------------------------------------------------------------------------------
	Collection(){}

	Collection(int size) : collection(size) {}

	Collection(const Collection& other) {
		add(other.getItems());
	}

	Collection(const std::vector<T>& items) {
		add(items);
	}

	Collection& operator=(const Collection& other) {
		add(other.getItems());
		return *this;
	}

	int getSize() const {
		return collection.size();
	}

	std::vector<T> getItems() const {
		return collection;
	}

	void add(const T& el) {
		collection.push_back(el);
	}

	void add(const std::vector<T>& items) {
		for (T item : items) {
			collection.push_back(item);
		}
	}

	void add(const Collection<T>& items) {
		add(items.collection);
	}

	T & operator[](int index)
	{
		return collection[index];
	}

	T operator[](int index) const
	{
		return collection[index];
	}

	void clear() {
		collection.clear();
	}

	T remove(int index) {
		T el = collection[index];
		collection.erase(collection.begin() + index);
		return el;
	}

	int getIndex(const T& item) const {
		return std::find(collection.begin(), collection.end(), item) - collection.begin();
	}

	bool exist(const T& item) const {
		if (std::find(collection.begin(), collection.end(), item) != collection.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(const Collection<T>& other) const {
		return collection == other.collection;
	}

	T getNext(const T& item) {
		return collection[(getIndex(item) + 1) % collection.size()];
	}

	iterator begin() {
		return iterator(collection, 0);
	}

	const_iterator begin() const
	{
		return const_iterator(collection, 0);
	}

	iterator end() {
		return iterator(collection, collection.size());
	}

	const_iterator end() const
	{
		return const_iterator(collection, collection.size);
	}
};

#endif