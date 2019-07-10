#include <iostream>
#include "./cppjieba/include/cppjieba/Jieba.hpp"
using namespace std;
int main(int , char **)
{
    char ch0[]={"金古江湖战旗春秋"};
    const char* const DICT_PATH = "./cppjieba/dict/jieba.dict.utf8";
    const char* const HMM_PATH = "./cppjieba/dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "./cppjieba/dict/user.dict.utf8";
    const char* const IDF_PATH = "./cppjieba/dict/idf.utf8";
    const char* const STOP_WORD_PATH = "./cppjieba/dict/stop_words.utf8";

    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    vector<string> words;
    vector<cppjieba::Word> jiebawords;
    string s=ch0;
    string result;

    jieba.Cut(s, words, true);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    return 0;

}
