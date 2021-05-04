// C++ program for Huffman Coding
#include <bits/stdc++.h>
using namespace std;

// A Huffman tree node
struct MinHeapNode
{

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)

    {

        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare
{

    bool operator()(MinHeapNode *l, MinHeapNode *r)

    {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode *root, string str, unordered_map<char, string> &charCode)
{

    if (!root)
        return;

    if (root->data != '*')
        charCode[root->data] = str;

    printCodes(root->left, str + "0", charCode);
    printCodes(root->right, str + "1", charCode);
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
unordered_map<char, string> HuffmanCodes(unordered_map<char, int> chars)
{
    unordered_map<char, string> charCode;
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

    for (auto const &item : chars)
    {
        minHeap.push(new MinHeapNode(item.first, item.second));
    }

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode('*', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using
    // the Huffman tree built above
    printCodes(minHeap.top(), "", charCode);
    return charCode;
}

unordered_map<char, int> readInput(char *fileName)
{
    unordered_map<char, int> freq;
    ifstream f;
    f.open(fileName);
    char temp;
    while (f.get(temp))
    {
        if (freq.find(temp) == freq.end())
        {
            freq[temp] = 1;
        }
        else
        {
            freq[temp]++;
        }
    }
    f.close();
    return freq;
}

string charToCode(unordered_map<char, string> charCode, char *fileName)
{
    string code = "";
    ifstream f(fileName);
    char temp;
    while (f.get(temp))
    {
        charCode.find(temp);
        code += charCode[temp];
    }
    f.close();
    return code;
}
char str_to_char(string binaryString)
{
    stringstream sstream(binaryString);
    bitset<8> bits;
    sstream >> bits;
    return char(bits.to_ulong());
}
void storeHuffmanunordered_map(ofstream &out, unordered_map<char, string> huffmanunordered_map)
{
    for (auto const &item : huffmanunordered_map)
    {
        if (item.first == '\n')
        {
            out << "\\n:" << item.second << endl;
        }
        else
        {
            out << item.first << ":" << item.second << endl;
        }
    }
    out << "**" << endl;
}
void compress(char *chr)
{
    clock_t t1, t2;
    t1 = clock();
    unordered_map<char, string> huffmanunordered_map = HuffmanCodes(readInput(chr));
    string huffmanCode = charToCode(huffmanunordered_map, chr);
    int padding;
    if (huffmanCode.length() % 8 != 0)
    {
        padding = 8 - huffmanCode.length() % 8;
        for (int x = 0; x < padding; x++)
            huffmanCode += "0";
    }
    string outfile = "output.txt";
    ofstream f(outfile.c_str(), std::ofstream::binary);
    f << padding << endl;
    int i = 0;
    storeHuffmanunordered_map(f, huffmanunordered_map);
    while (true)
    {
        char temp = str_to_char(huffmanCode.substr(i, 8));
        f << temp;
        i += 8;
        if (i >= huffmanCode.length())
            break;
    }
    f.close();
    t2 = clock();
    double time = ((double)t2 - (double)(t1)) / (double)CLOCKS_PER_SEC;
    cout << "time elapsed: " << time << endl;
}
void getHuffmanCodesFromFile(ifstream &f, int *padding, unordered_map<char, string> &huffmanCodes)
{
    char temp;
    if (f.is_open())
    {
        f.get(temp);
        f.get();
        *padding = temp - 48;
        bool flag = true;
        char temp1, temp2;
        while (f.get(temp1))
        {

            f.get(temp2);
            if (temp1 == '*' && temp2 == temp1)
            {
                f.get();
                break;
            }
            if (flag)
            {

                char colon = ':';
                if (colon - temp2)
                {
                    string temp3;
                    f.get();
                    getline(f, temp3);
                    huffmanCodes[(char)10] = temp3;
                    flag = false;
                }
                else
                {
                    string code;
                    getline(f, code);
                    huffmanCodes[temp1] = code;
                }
            }
            else
            {
                string code;
                getline(f, code);
                huffmanCodes[temp1] = code;
            }
        }
    }
}
string char_to_str(char ch)
{
    bitset<8> temp(ch);
    return temp.to_string();
}

void decompress(char *filename)
{
    clock_t t1, t2;
    t1 = clock();
    ifstream f(filename, std::ifstream::binary);
    int padding = 0;
    unordered_map<char, string> huffmanCodes;
    getHuffmanCodesFromFile(f, &padding, huffmanCodes);
    char temp;
    string huffmanCode = "";
    while (f.get(temp))
    {
        huffmanCode += char_to_str(temp);
    }
    huffmanCode = huffmanCode.substr(0, huffmanCode.length() - padding);
    cout << huffmanCode.length() << " " << huffmanCodes.size() << endl;
    string outfile = "decompressed.txt";
    ofstream decompressedOut(outfile.c_str(), std::ofstream::binary);
    int i = 0;
    while (i < huffmanCode.length())
    {
        for (auto const &item : huffmanCodes)
        {
            if (huffmanCode.substr(i, item.second.length()) == item.second)
            {
                decompressedOut << item.first;
                i += item.second.length();
                break;
            }
        }
    }
    f.close();
    for (auto const &item : huffmanCodes)
        cout << item.first << " : " << item.second << endl;
    t2 = clock();
    double time = ((double)t2 - (double)(t1)) / (double)CLOCKS_PER_SEC;
    cout << "time elapsed: " << time << endl;
}

// Driver program to test above functions
int main()
{

    string fileName;
    cout << "please enter the desired file name: ";
    cin >> fileName;
    int mode;
    do
    {
        cout << "please choose the mode (1: compress, 2: decompress, 3: exit): ";
        cin >> mode;
    } while (!(mode > 0 && mode < 4));
    char *chr = const_cast<char *>(fileName.c_str());
    switch (mode)
    {
    case 1:
        compress(chr);
        break;
    case 2:
        decompress(chr);
        break;
    case 3:
        exit(0);
    default:
        break;
    }
    return 0;
}
