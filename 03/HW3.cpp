#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>

void Solution1(){
int N, value;
std::cin>>N;
std::set<int> st;

while(N-->0) {
    std::cin >> value;
    st.insert(value);
}

std::cout<<st.size()<<std::endl;
}

void Solution2(){
    std::string jewels, stones;
    std::cin>>jewels>>stones;
    std::set<char> st;

    for(int i = 0;i<jewels.size();++i)
        st.insert(jewels[i]);

    unsigned count =0;

    for(int i=0;i<stones.size();++i){
        auto it = st.find(stones[i]);
        if(it != st.end())
            ++count;
    }
std::cout<<count<<std::endl;
}

void Solution3(){
    std::string s;
    std::cin>>s;
    std::set<char> st;

    int n = s.size();
    int left = 0;
    int right = 0;
    int max_sub_string =0;

    while (right < n) {
        if (st.find(s[right]) == st.end()) {
            st.insert(s[right]);
            max_sub_string = std::max(max_sub_string, right - left + 1);
            right++;
        } else {
            st.erase(s[left]);
            left++;
        }
    }

    std::cout<<max_sub_string<<std::endl;
}

void Solution4(){
  std::string s;
  std::cin>>s;
  std::map<char, bool> mp;// Chekcing if is char unique or not
  std::map<char, int> mp2;// Saving the indexes

  for(int i =0;i<s.size();++i){
      if(mp.find(s[i]) == mp.end()) {
          mp.insert(std::make_pair(s[i], true));
          mp2[s[i]] = i;
      }
      else{
          mp[s[i]] = false;
      }
  }
for(auto it = mp.begin(); it!=mp.end();++it){
    if(it->second == true) {
        std::cout << mp2[it->first] << std::endl;
        return;
    }
}
  std::cout<<"-1"<<std::endl;
}

void Solution5(){
std::string s;
std::cin>>s;

std::unordered_map<char, int> mp;// Counting amount of char appearance

for(auto ch :s)
    mp[ch]++;

unsigned max_size = 0;
bool hasOddFrequency = false;

for(const auto& pair : mp){
    max_size += (pair.second/2) * 2;
    if(pair.second %2 != 0)
        hasOddFrequency = true;
}

if(hasOddFrequency)
    max_size++;

std::cout<<max_size<<std::endl;


}

void Solution6(){
    int N, k,value;
    std::vector<int> nums;
    std::cin>>N;

    while(N-->0) {
        std::cin >> value;
        nums.push_back(value);
    }
    std::cin>>k;
    std::map<int, int> numIndexMap;

    for (int i = 0; i < nums.size(); ++i) {
        auto it = numIndexMap.find(nums[i]);

        if (it != numIndexMap.end() && i - it->second <= k) {
            std::cout<<"true"<<std::endl;
            return;
        }

        numIndexMap[nums[i]] = i;
    }

    std::cout<<"false"<<std::endl;
}


void Solution7(){
std::string pattern , s;
std::getline(std::cin,pattern);
std::getline(std::cin,s);

std::unordered_map <char, std::string> charToWord;
std::unordered_map <std::string, char> wordToChar;

std::istringstream iss(s);
std::vector<std::string> words;
while(iss>>s)
    words.push_back(s);

if(pattern.size() != words.size()) {
    std::cout << "false"<<std::endl;
    return;
}

    for (int i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        std::string word = words[i];

        if (charToWord.find(c) == charToWord.end() && wordToChar.find(word) == wordToChar.end()) {
            charToWord[c] = word;
            wordToChar[word] = c;
        } else if (charToWord[c] != word || wordToChar[word] != c) {
                std::cout<<"false"<<std::endl;
                return;
            }
        }
    std::cout<<"true"<<std::endl;
    }

void Solution8(){
 std::string s;
 std::cin>>s;

    std::unordered_map<char, int> charFrequency;

    for (char ch : s)
        charFrequency[ch]++;

    auto compare = [&](char a, char b) {
        return charFrequency[a] < charFrequency[b];
    };

    std::priority_queue<char, std::vector<char>, decltype(compare)> maxHeap(compare);

    for (const auto& pair : charFrequency)
        maxHeap.push(pair.first);

    std::string result;
    while (!maxHeap.empty()) {
        char currentChar = maxHeap.top();
        maxHeap.pop();
        result += std::string(charFrequency[currentChar], currentChar);
    }

   std::cout<<result<<std::endl;
}

class Trie {
    class TrieNode {
    public:
        std::map<char, TrieNode *> children;
        bool isEndOfWord;

        TrieNode() {
            isEndOfWord = false;
        }
    };

    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        // Also add the destructor...
    }

    void insert(const std::string &word) {
        TrieNode *current = root;
        for (char ch: word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool startsWith(const std::string &prefix) {
       auto current = root;

       for(auto ch: prefix){
           if(current->children.find(ch) == current->children.end()){
               return false;
           }
           current = current->children[ch];
       }
       return true;
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int calculateSubtreeSum(TreeNode* node, std::unordered_map<int, int>& sumFrequency, int& maxFrequency) {
    if (!node) {
        return 0;
    }

    int leftSum = calculateSubtreeSum(node->left, sumFrequency, maxFrequency);
    int rightSum = calculateSubtreeSum(node->right, sumFrequency, maxFrequency);

    int subtreeSum = leftSum + rightSum + node->val;
    sumFrequency[subtreeSum]++;

    maxFrequency = std::max(maxFrequency, sumFrequency[subtreeSum]);

    return subtreeSum;
}

    std::vector<int> findFrequentTreeSum(TreeNode* root) {
        std::unordered_map<int, int> sumFrequency;
        int maxFrequency = 0;

        calculateSubtreeSum(root, sumFrequency, maxFrequency);

        std::vector<int> result;
        for (const auto& pair : sumFrequency) {
            if (pair.second == maxFrequency) {
                result.push_back(pair.first);
            }
        }

        return result;
    }

int main() {
    //Set
//Solution1();
//Solution2();
//Solution3();

    //Map
//Solution4();
//Solution5();
//Solution6();
//Solution7();
//Solution8();

//Solution 9
    Trie trie;
    trie.insert("Hello");
    trie.insert("Hey");
    trie.insert("World");

    std::cout << trie.startsWith("Hell") << std::endl; // Output: true
    std::cout << trie.startsWith("abc") << std::endl;  // Output: false
    std::cout << trie.startsWith("Wo") << std::endl;  // Output: true


//Solution 10
//TreeNode* node= new TreeNode(5, new TreeNode(2), new TreeNode(-3));
//findFrequentTreeSum(node);
//delete node;
}
