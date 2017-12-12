#include "ds.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

//simple test for union find

void testUnionFind() {
    UnionFind graph = UnionFind();
    graph.add(1);
    graph.add(2);

    assert(!graph.conn(1, 2));
    graph.merge(1, 2);
    assert(graph.conn(1, 2));
}

void testSplayTree() {
    SplayTree* tree = new SplayTree();
    //todo
}


void testFullDynamic(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_2_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
    ifs >> N;
    std::string cmd;
    std::vector<int> commands;
    std::vector<bool> results;
    int a, b;
    while(ifs >> cmd >> a >> b) {
        if(cmd == "add") {
            commands.push_back(0);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "rem") {
            commands.push_back(1);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "conn") {
            commands.push_back(2);
            commands.push_back(a);
            commands.push_back(b);

        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    FullDynamic graph = FullDynamic();
    for(int i = 0; i < N; i++) {
        graph.add(i);
    }
    for(int i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0)
            graph.link(a, b);
        else if(c == 1)
            graph.cut(a, b);
        else if(c == 2) {
            results.push_back(graph.conn(a, b));
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "FullDynamic took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";

    for(auto res: results) {
        if(res) {
            ofs << "YES\n";
        } else {
            ofs << "NO\n";
        }
    }
}

void testETT(int size) {
    std::string sz = std::to_string(size);
    std::string infile = "tests/tree_tests/tree_" + sz +".txt";
    std::string outfile = "tests/tree_tests/tree_answer_3_" + sz +".txt";
    std::ifstream ifs(infile, std::ifstream::in);
    std::ofstream ofs(outfile, std::ofstream::out);
    int N;
    ifs >> N;
    std::string cmd;
    std::vector<int> commands;
    std::vector<bool> results;
    int a, b;
    while(ifs >> cmd >> a >> b) {
        if(cmd == "add") {
            commands.push_back(0);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "rem") {
            commands.push_back(1);
            commands.push_back(a);
            commands.push_back(b);
        } else if(cmd == "conn") {
            commands.push_back(2);
            commands.push_back(a);
            commands.push_back(b);

        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    EulerTourTree graph = EulerTourTree();
    // for(int i = 0; i < N; i++) {
    //     graph.add(i);
    // }
    for(int i = 0; i < commands.size(); i += 3){
        int c = commands[i];
        int a = commands[i+1];
        int b = commands[i+2];
        if(c == 0)
            graph.link(a, b);
        else if(c == 1)
            graph.cut(a, b);
        else if(c == 2) {
            results.push_back(graph.conn(a, b));
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "ETT took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";

    for(auto res: results) {
        if(res) {
            ofs << "YES\n";
        } else {
            ofs << "NO\n";
        }
    }
}

void testAll(int size) {
    testUnionFind();
    testSplayTree();
    testFullDynamic(size);
    testETT(size);
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testAll(100);
    return 0;
}
