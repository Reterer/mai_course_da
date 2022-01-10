#pragma once
#include <map>
#include <string>
#include <vector>

namespace NSuffixTree {

struct TNode {
    std::map<char, TNode*> Next;
    TNode* Suff;

    int Begin;
    int End;

    TNode(int begin, int end);
    ~TNode();
};

class TSuffixTree {
public:
    std::string Text;
    TNode* Root;
    TNode* CurrNode;
    int End;
    int Rem;
    int CurrLen;
    int CurrEdge;

    void Solve();
    TSuffixTree(const std::string& textA, const std::string& textB);
    ~TSuffixTree();
private:
    int IdxFirstSep;
    int dfs(std::vector<std::pair<int,int>>& ans, int& maxLen, TNode* node, int len, int begin);
    void Iterate(int i);
};

}   // namespace NSuffixTree