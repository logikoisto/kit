// 一个 非线程安全的 跳表实现
#ifndef _KIT_SKIPLIST__
#define _KIT_SKIPLIST__
#include <cstdlib>
#include <string>
#include <vector>
#include "vector"
namespace KIT_NAMESPACE {
    const int  MAX_LEVEL = 32; // 跳表节点的最大层数
    const double  PROBABILITY  = 0.25;
    // 节点
    struct  Node{
        // Node** level; //双重指针初始化数组
        std::vector<Node*> level; // 这里动态调整 会更加节省内存
        std::string key; // key
        int val;      // 值
    };
    // 跳表实现的类
    class SkipList {
        public:
            // // 禁止copy
            // SkipList(const SkipList&) = delete;
            // void operator=(const SkipList&) = delete;
            
            // init 初始化跳表
            SkipList(){}
            ~SkipList(){}
            // get 根据key查询value 如果不存在就返回null
            int get(const std::string& key) const {
                Node* prev =  _search(key)[0];
                if(prev->level[0] && prev->level[0]->key == key){
                    return prev->level[0]->val;
                }
                return -1;
            }

            // set 根据key插入value 如果key存在就更新其value,否则插入新的位置
            void set(const std::string& key, int value){
                auto prevs = _search(key);
                int level = random_level();
                if (level > maxlevel){
                    for(int i = maxlevel; i < level; ++i){
                        prevs[i] = head;
                    }
                    maxlevel = level;
                }
                Node* cur = new Node();
                cur->key = key;
                cur->val = value;
                for (int i = level - 1; i >= 0; --i){
                    cur->level[i] = prevs[i]->level[i];
                    prevs[i]->level[i] = cur;
                }
            }

            // del 根据key删除value
            bool del(const std::string& key){
                auto prevs = _search(key);
                if(!prevs[0]->level[0] || prevs[0]->level[0]->key != key ){
                    return false;
                }
                Node* d = prevs[0]->level[0];
                for(int i = 0; i < maxlevel; i++){
                    if(prevs[i] -> level[i] == d){
                        prevs[i]->level[i] = d->level[i];
                    }
                }
                delete d;
                while (maxlevel > 1 && !head->level[maxlevel-1]) {
                    maxlevel --;
                }
                return true;
            }
        private:
            Node* head;
            int maxlevel = 1;
            // 返回具体的被查询到的节点
            std::vector<Node*> _search(const std::string& key)const{
                Node* cur = head; 
                std::vector<Node*> prevs(MAX_LEVEL);
                for(int i = maxlevel - 1;i >= 0;--i){
                    while(cur->level[i] && cur->level[i]->key < key){
                        cur = cur->level[i];
                    }
                    prevs[i] = cur;
                }
                return prevs;
            }
            // 返回一个随机的层数
            int random_level(){
                srand((unsigned)time(NULL));
                int level = 1;
                while (std::rand()/double(RAND_MAX) < PROBABILITY && level < MAX_LEVEL ) {
                    level++;
                }
                return level;
            }
    };
};

#endif