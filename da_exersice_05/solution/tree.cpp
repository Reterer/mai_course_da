#include <vector>
#include <iostream>
#include "tree.hpp"

namespace NSuffixTree {

const char SECOND_SEP = '$';
const char FIRST_SEP = '#';

TNode::TNode(int begin, int end)
    : Begin(begin), End(end)
{}

TNode::~TNode() {
    for(auto& it : Next) {
        delete it.second;
    }
}

TSuffixTree::TSuffixTree(const std::string& textA, const std::string& textB) {
    Root = new TNode(0, 0);
    Root->Suff = Root;

    CurrNode = Root;
    CurrLen = 0;
    CurrEdge = 0;
    Rem = 0;
    IdxFirstSep = textA.size();

    Text = textA + FIRST_SEP + textB + SECOND_SEP;
    End = 0;
    for(int i = 0; i < (int)Text.length(); i++){
        Iterate(i);
        End++;
    }
}

void TSuffixTree::Iterate(int i){
    TNode* prevInsertedNode = nullptr;
    Rem++;

    if (Rem == 1) {
        CurrEdge = i;
    }

    while (Rem > 0) {
        auto nextIt = CurrNode->Next.find(Text[CurrEdge]);
        TNode* nextNode = (nextIt != CurrNode->Next.end() ? nextIt->second : nullptr);

        if (nextNode == nullptr) {
            CurrNode->Next[Text[CurrEdge]] = new TNode(i, -1);
            if (prevInsertedNode != nullptr) {
                prevInsertedNode->Suff = CurrNode;
            }
            prevInsertedNode = CurrNode;
        } else {
            int edgeLen = nextNode->End == -1 ? End - nextNode->Begin + 1 : nextNode->End - nextNode->Begin;

            if (CurrLen >= edgeLen) {
                CurrNode = nextNode;
                CurrLen -= edgeLen;
                CurrEdge += edgeLen;
                continue; 
            }

            if (Text[nextNode->Begin + CurrLen] == Text[i]) {
                CurrLen++;
                if (prevInsertedNode != nullptr) {
                    prevInsertedNode->Suff = CurrNode;
                }
                break; 
            }

            TNode* midNode = new TNode(nextNode->Begin, nextNode->Begin + CurrLen);
            CurrNode->Next[Text[CurrEdge]] = midNode;
            midNode->Next[Text[i]] = new TNode(i, -1);
            nextNode->Begin += CurrLen;
            midNode->Next[Text[nextNode->Begin]] = nextNode;

            if (prevInsertedNode != nullptr) {
                prevInsertedNode->Suff = midNode;
            }
            prevInsertedNode = midNode;
        }

        
        if (CurrNode == Root && CurrLen > 0) {
            CurrEdge++;
            CurrLen--;
        }else if (CurrNode != Root) {
            CurrNode = CurrNode->Suff;
        }
                
        Rem--;
    }
}

int TSuffixTree::dfs(std::vector<std::pair<int,int>>& ans, int& maxLen, TNode* node, int len, int begin) {
    if (node->End == -1 && node->Begin <= IdxFirstSep) {
        return 1;
    }
    if (node->End == -1 && node->Begin > IdxFirstSep) {
        return 2; 
    }

    bool wasFirst = false;
    bool wasSecond = false;
    
    len = len + node->End - node->Begin;
    begin = node->End - len;

    for (auto& it : node->Next) {
        int res = dfs(ans, maxLen, it.second, len, (len == 0 ? it.second->Begin : begin));
        if (res == 1)
            wasFirst = true;
        if (res == 2)
            wasSecond = true;
    }

    if (len != 0 && wasFirst && wasSecond) {
        if(maxLen == len) {
            ans.push_back({begin, len});
        } else if (maxLen < len) {
            maxLen = len;
            ans.clear();
            ans.push_back({begin, len});
        }     
    }

    if (wasFirst && !wasSecond)
        return 1;
    if (wasSecond && !wasFirst)
        return 2;
    return 0;
}

void TSuffixTree::Solve() {
    std::vector<std::pair<int,int>> ans;
    int maxLen = 0;

    dfs(ans, maxLen, Root, 0, 0);

    // std::cout << maxLen << '\n';
    // for (auto& el : ans) {
    //     std::cout << Text.substr(el.first, el.second) << '\n';
    // }
}

TSuffixTree::~TSuffixTree() {
    delete Root;
}

}   // namespace NSuffixTree