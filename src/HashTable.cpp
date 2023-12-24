#include "HashTable.h"

// Explicit instantiations
// ---------------------------------------------------------
#pragma region
template class HashTable<int>;
template class HashTable<float>;
template class HashTable<double>;
template class HashTable<char>;
template class HashTable<wchar_t>;
template class HashTable<bool>;
template class HashTable<std::string>;

// overload hash_function: HashTable<std::string>
template <> int HashTable<std::string>::hash_function(const std::string& key) const {
	// BEGIN
	
	// Convert each character in the string to its ASCII value and calculate the key value
	ull keyValue = 0;
	for (char chr : key) {
		if (keyValue > (ULLONG_MAX - chr) / 256) {
			// Handle overflow by breaking out of the loop
			break;
		}
		keyValue = keyValue * 256 + chr;
	}

	// Calculate the decimal part of hash value using fmod
	double decimal_part = std::fmod(static_cast<double>(keyValue) * A, 1.00);

	// Return the hash value
	return static_cast<int>(this->size * decimal_part);
	// END
}
#pragma endregion
// ---------------------------------------------------------


// Private methods
// ---------------------------------------------------------
#pragma region
// calculating hash value
template <class T> int HashTable<T>::hash_function(const T& inpKey) const {
	// BEGIN: Calculate hash value h(k) = floor(m * [(k * A) mod 1])

	// Chech if constexpr (std::is_same_v<T, std::string>)
	
	// Calculate the decimal part of hash value using fmod
	double decimal_part = std::fmod(static_cast<double>(inpKey) * A, 1.00);

	// Return the hash value
	return static_cast<int>(std::floor(this->size * decimal_part));

	// END
}
#pragma endregion
// ---------------------------------------------------------


// Constructor & destructor
// ---------------------------------------------------------
#pragma region
// Constructor for the HashTable class.
template <class T> HashTable<T>::HashTable(const int& m, const std::string& filename) {
	// BEGIN: contructor

	 // 1. Initialize member variables
	this->table = nullptr;
	this->size = m;

	// 2. Open the output file and check for success.
	this->output.open(filename);
	if (this->output.is_open() == false) {
		// If the file opening fails, throw a runtime_error with an appropriate message.
		throw std::runtime_error("+ khong the mo duong dan toi tap tin chua du lieu output\n");
	}

	// 3. Switch back to sync with stdio.
	std::ios_base::sync_with_stdio(false);

	// 4. Allocate memory for the table array using nothrow, and check for success.
	this->table = new (std::nothrow) HashEntry[ this->size ]();

	std::string getname = filename;
	size_t pos = filename.find_last_of("\\");
	if (pos != std::string::npos) {
		getname = filename.substr(pos + 1, filename.length());
	}

	if (!this->table || this->size < 1) {
		// If memory allocation fails, log the failure message.
		this->output << "[constructor] - khoi tao khong thanh cong\n";
		this->output << "+ cap phat khong thanh cong bang T do " << (m < 1 ? "m khong hop le\n" : "khong du bo nho cap phat\n");
		this->output << "+ m = " << m << "\n";
		this->output << "+ output file = " << getname;

		this->output.close();

		// Switch back to sync with stdio.
		std::ios_base::sync_with_stdio(true);

		std::cout << "[^^] Complete!\n";
		exit(-1);
	}
	else {
		// If memory allocation is successful, log the success message.
		this->output << "[constructor] - khoi tao thanh cong\n";
		this->output << "+ m = " << m << "\n";
		this->output << "+ output file = " << getname << "\n";
	}

	// END
}

template <class T> HashTable<T>::~HashTable() {
	// BEGIN: Destructor

	int count = 0;
	if (this->table != nullptr) {
		// 1. Iterate through each element in the table array and count collision elements
		for (int idx = 0; idx < this->size; idx++) {
			HashEntry& entry = this->table[ idx ];
			// If the element is not nullptr.
			if (entry != nullptr) {

				// update the collision count.
				int entryCol = entry->count_collisions();
				count += entryCol;

				// delete the entry
				delete entry;
				entry = nullptr;
			}
		}
		// 2. Delete the table array
		delete[] this->table;
		this->table = nullptr;
	}

	// 4. Log the destruction message
	this->output << "[destructor] - huy bo thanh cong\n";
	this->output << "+ so phan tu xung dot da delete = " << count << "\n";
	this->output << "+ da delete bang T";
	this->output.flush();
	this->output.close();

	// . Switch back to sync with stdio
	std::ios_base::sync_with_stdio(true);

	// END
}
#pragma endregion
// ---------------------------------------------------------


// Public methods
// ---------------------------------------------------------
#pragma region
template <class T> HashNode<T>** HashTable<T>::get_table() const {
	// BEGIN: Get the hash table

	// Return
	return this->table;

	// END
}

template <class T> int HashTable<T>::get_size() const {
	// BEGIN: Get the size of the hash table

	// Return
	return this->size;

	// END
}

template <class T> void HashTable<T>::insert(const T& inpKey) {
	// BEGIN: Insertion Process

    // 1. Calculate the hash value for the given key
	int hashValue = hash_function(inpKey);

	// 2. Access the entry at the calculated hash value
	HashEntry& entry = this->table[ hashValue ];

	bool collision = false;
	// 3. Check if the slot is empty
	if (entry == nullptr) {
		// 3.1 If empty, create a new HashNode and insert the key
		entry = new HashNode<T>(inpKey);
	}
	else {
		// 3.2 If not empty, insert the key into the existing HashNode (handle collision)
		entry->insert(inpKey);
		collision = true;
	}

	// 4. Print success message and information about the inserted key
	this->output << "- thanh cong\n";
	this->output << "+ key = " << inpKey << "\n";
	this->output << "+ hash value = " << hashValue << "\n";
	this->output << "+ xung dot: [" << (collision ? "co" : "khong") << "]\n";

	// END
}

template <class T> void HashTable<T>::save_result_insert_list(const T* insertList, const int& sizeList) {
	// BEGIN: Save result of insert list

	// Step 1: Traverse the insert list
	for (int idx = 0; idx < sizeList; idx++) {
		// Log information for the current insert operation
		this->output << "[Insert " << idx + 1 << "] ";

		// Call the insert function for the current element in the insert list
		this->insert(insertList[ idx ]);
	}

	// END
}

template <class T> void HashTable<T>::search(const T& inpKey) {
	// BEGIN: Search for key in the HashMap

	// 1. Calculate the hash value for the key.
	int hashValue = hash_function(inpKey);

	bool found = false;
	bool collision = false;

	// 2. Check if the element at the hash value is nullptr.
	HashNode<T>* entry = this->table[hashValue];
	if (entry != nullptr) {
		// 2.1 Check if the key matches the key in the current entry.
		if (entry->get_key() == inpKey) {
			// Key found in the primary location
			found = true;
		}
		// If not, search for the key in the collision resolution chain.
		else {
			collision = found = entry->search(inpKey);
		}
	}
	
	// 3. Output search result and information about the key
	this->output << (found ? "- tim thay\n" : "- khong tim thay\n");
	this->output << "+ key = " << inpKey << "\n";
	this->output << "+ hash value = " << hashValue << "\n";
	this->output << "+ xung dot: [" << (collision ? "co" : "khong") << "]\n";

	// END
}

template <class T> void HashTable<T>::save_result_search_list(const T* searchList, const int& sizeList) {
	// BEGIN: Save result of search list

	for (int idx = 0; idx < sizeList; idx++) {
		// Log information for the current search operation
		this->output << "[Search " << idx + 1 << "] ";

		// Call the search function for the current element in the search list
		this->search(searchList[ idx ]);
	}

	// END
}

template <class T> void HashTable<T>::print_table(const std::string& filename) {
	// BEGIN: Print the hash table to a file

	// 1. Open the file for writing
	std::ofstream stream;
	stream.open(filename);

	// 2. Check if the file is successfully opened
	if (!stream.is_open()) {
		// If the file cannot be opened, return without printing
		return;
	}

	// 3. Save the hash map to the file
	stream << *this;

	// 4. Flush the stream and close the file
	stream.flush();
	stream.close();

	// END
}

template <class T> void HashTable<T>::display() {
	// BEGIN
	std::cout << *this << "\n";
	// END
}
#pragma endregion
// ---------------------------------------------------------


// Friend
// ---------------------------------------------------------
#pragma region
template <class T> std::ostream& operator<<(std::ostream& os, const HashTable<T>& inpMap) {
	// BEGIN

	for (ull idx = 0; idx < inpMap.get_size(); idx++) {
		// 1. Print the index with padding
		os << "[" << std::setw(3) << std::setfill('0') << idx << "]:  ";

		// 2. Check if the element at the index is not nullptr, then print its content.
		if (inpMap.get_table()[ idx ] != nullptr) {
			os << *inpMap.get_table()[ idx ];
		}

		// 3. Check if it's not the last index, then print a newline.
		if (idx != inpMap.get_size() - 1) os << "\n";
	}
	return os;

	// END
}

template std::ostream& operator<<(std::ostream&, const HashTable<float>&);
template std::ostream& operator<<(std::ostream&, const HashTable<double>&);
template std::ostream& operator<<(std::ostream&, const HashTable<char>&);
template std::ostream& operator<<(std::ostream&, const HashTable<wchar_t>&);
template std::ostream& operator<<(std::ostream&, const HashTable<bool>&);
template std::ostream& operator<<(std::ostream&, const HashTable<std::string>&);
#pragma endregion
// ---------------------------------------------------------