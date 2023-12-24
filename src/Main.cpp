//#include "TreeNode.h"
//#include "TreeNode.cpp"
//#include "AVLTree.h"
//#include "HashNode.h"
//#include "HashTable.h"
#include "Header.h"

using namespace std;

int main(int argc, char** argv) {
    // 1. BEGIN: Check if the correct number of command line arguments is provided

    if (argc != 2) {
        std::cerr << "[Error]: Invalid command line argument\n";
        std::cout << "[Usage]: program.exe path\n";
        std::cout << "[Usage]: program.exe filename\n";
        return 1;
    }

    // 2. BEGIN: Load data from the file
    std::fstream stream;
    stream.open(argv[ 1 ], std::ios_base::in);
    if (!stream.is_open()) {
        std::cerr << "[!] Can't open (path of) file \"" << argv[ 1 ] << "\"\n";
        return 1;
    }

    // File name contains output data
    std::string output_filename;
    stream >> output_filename;

    // Number of elements(m) of table T
    int m;
    stream >> m;

    // Number of elements to insert into the hash table
    int insertSize = 0;
    stream >> insertSize;

    // Allocate memory for the insert list and read its content
    int* insertList = new int[ insertSize ];
    for (int idx = 0; idx < insertSize; idx++) {
        stream >> insertList[ idx ];
    }

    // Number of elements to search
    int searchSize = 0;
    stream >> searchSize;

    // Allocate memory for the search list and read its content
    int* searchList = new int[ searchSize ];
    for (int idx = 0; idx < searchSize; idx++) {
        stream >> searchList[ idx ];
    }

    // 2. END: load from file
    stream.close();

	

	// 3. BEGIN: create HashMap<int> and process the resulting path
	output_filename = get_path_file(output_filename);

	try {
        // Create a HashMap object
		HashTable<int> hashMap(m, output_filename);

        // Save the result of inserting elements from the insert list
		hashMap.save_result_insert_list(insertList, insertSize);

        // Save the result of searching elements from the search list
		hashMap.save_result_search_list(searchList, searchSize);

        // Print the hash table to the display file
        hashMap.print_table(_DISPLAY_PATH_);
	}
	catch (const std::runtime_error& ex) {
        // If an exception occurs, log the result (error) message to the default output file
		
        stream.open(_DEFAULT_OUTPUT_PATH_, std::ios_base::out);
		if (stream.is_open() == false) exit(-1);

		stream << "[constructor] - khoi tao khong thanh cong\n";
		stream << ex.what();
		stream << "+ m = " << m << "\n";
		stream << "+ output file = " << output_filename;
		
        stream.flush();
		stream.close();
	}


	std::cout << "[^^] Complete!\n";

	return 0;
	
    // End main
}

//"D:\HashTable\src\test.txt"