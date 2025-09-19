#include "mainwindow.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "custom_list.h"
#include "binary_tree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::vector<std::string> words = read_file_text();

    binary_tree<std::string> Tree;

    for (std::string word : words) {
        Tree.insert(word);
    }

    std::cout << std::endl;

    std::vector<std::string> res = Tree.inorder_traversal();

    for (std::string word : res) {
        std::cout << word << " ";
    }


    w.show();
    return a.exec();
}

std::string cleanWord(const std::string& word) {
    std::string result;
    
    std::copy_if(word.begin(), word.end(), std::back_inserter(result),
                [](char c) { return std::isalnum(c); });
        
    std::transform(result.begin(), result.end(), result.begin(),
                [](char c) { return std::tolower(c); });
    
    return result;
}

std::vector<std::string> read_file_text() {
    std::ifstream file("C:/Projects/text.txt");
    
    if (!file.is_open()) {
        std::cerr << "Can't open file!" << std::endl;
        return {};
    }
    
    std::vector<std::string> words((std::istream_iterator<std::string>(file)), 
                                    std::istream_iterator<std::string>());
    
    file.close();
    
    for (int i = 0; i < words.size(); i++) {
        words[i] = cleanWord(words[i]);
        std::cout << words[i] << std::endl;
    }
    
    return words;
}
