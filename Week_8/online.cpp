#include<bits/stdc++.h>
using namespace std;

vector<string> keyHolder;

int deleteNumber = 0;
int insertionNumber = 0;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int originalSizeOfHashTable(int n){
    if(isPrime(n)) return n;
    n = originalSizeOfHashTable(n+1);
    return n;
}


class HashTable{

    public:
    vector<string> answer;
    int maxSize;
    int NodeCounter = 0;
    bool linkedList ;
    bool doubleHasing ;
    bool customProbing ;
    bool Hash_one_1 ;
    bool Hash_two_2 ;

    class Node{
        public:

        string key;
        int value;
        Node * next;
        int prob;
        int collision;

        Node(string key,int value){
            this->key = key;
            this->value = value;
            next = NULL;
            prob = 0;
            collision = 0;
        }
    };

    Node **table;

    HashTable(int size){
        maxSize = size;
        table = new Node*[maxSize];
        for (int i = 0; i < maxSize; ++i) {
            table[i] = NULL;
        }
        linkedList = false;
        doubleHasing = false;
        customProbing = false;
        Hash_one_1 = false;
        Hash_two_2 = false;
    }

    void insert(string key,int value){

        Node * newNode = new Node(key,value);

        if(linkedList) insertUsingLinkedList(newNode);

        else if(doubleHasing)insertUsingDoubleHashing(newNode);

        else if(customProbing)insertUsingCustomProbe(newNode);

    }

    void insertUsingLinkedList(Node * newNode){
        int index = countWeight(newNode->key) % maxSize;
        newNode->prob++;
        
        if(table[index] == NULL){
            table[index] = newNode;
        }

        else{
            Node * temp = table[index];
            newNode->next = temp;
            table[index] = newNode;
            newNode->collision++;
            newNode->prob++;
            Node * temp2 = newNode->next;
            
            while(temp2!=NULL){
                int counter = 0;
                for(int i  = 0;i<temp2->key.size();i++){
                    if(abs(temp2->key[i] - newNode->key[i]) == 19 || abs(temp2->key[i] - newNode->key[i]) == 4){
                        counter++;
                    }
                }
                if(counter == newNode->key.size()){
                    answer.push_back(newNode->key);
                    answer.push_back(temp2->key);
                    break;
                }
                temp2= temp2->next;
            }
        }
        NodeCounter++;
    }

    vector<string> reverse_compl(){
        return answer;
    }

    void insertUsingDoubleHashing(Node * newNode){
        if(NodeCounter == maxSize){
            cout<<"Maximum amount reached !!"<<endl;
            return;
        }

        int index = doubleHash(newNode->key,newNode->prob);
        int i = 0;

        if(table[index] == NULL){
            table[index] = newNode;
            newNode->prob++;
        }
        else{
            while(i<maxSize){
                newNode->prob++;
                index = doubleHash(newNode->key,newNode->prob);
                if(table[index] == NULL){
                    table[index] = newNode;
                    newNode->prob++;
                    newNode->collision++;
                    break;
                }
            }
        }
        NodeCounter++;
    }

    void insertUsingCustomProbe(Node * newNode){
        if(NodeCounter == maxSize){
            cout<<"Maximum amount reached !!"<<endl;
            return;
        }

        int index = customProbe(newNode->key,newNode->prob);
        int i = 0;

        if(table[index] == NULL){
            table[index] = newNode;
            newNode->prob++;
        }

        else{
            while(i<maxSize){
                newNode->prob++;
                index = customProbe(newNode->key,newNode->prob);
                if(table[index] == NULL){
                    table[index] = newNode;
                    newNode->prob++;
                    newNode->collision++;
                
                    break;
                }
            }
        }
        NodeCounter++;
    }

    int countWeight(string s){
        int wordLength = s.length();
        int weight = 0;

        for(int i = 0;i<wordLength;i++){
            weight += s[i];
        }
        return weight;
    }
    
    void printTable(){
        for(int i = 0;i<maxSize;i++){
            if(table[i]!=NULL){
                Node * temp = table[i];
                while(temp!=NULL){
                    cout<<temp->key<<" "<<temp->value<<" "<<temp->prob<<endl;;
                    temp = temp->next;
                }
            }
            cout<<endl;
            cout<<endl;
        }
    }

    int Hash_one(string key){
        return (maxSize - (countWeight(key)%maxSize)) % maxSize;
    }
    
    int Hash_two(string key){
        return (4*(maxSize*2 - (countWeight(key) % maxSize)) )% maxSize;
    }

    int auxilaryHash(string key){
        int n = maxSize / 3;
        return ((n) - (countWeight(key)%n))%maxSize;
    }

    int doubleHash(string key,int prob){
        if(Hash_one_1)
            return (Hash_one(key) + (auxilaryHash(key) * prob))%maxSize;
        else return (Hash_two(key) + (auxilaryHash(key) * prob))%maxSize;
    }

    int customProbe(string key,int prob){
        if(Hash_one_1)
            return (Hash_one(key) + (2 * prob * auxilaryHash(key)) + (3*prob*prob))%maxSize;
        else return (Hash_two(key) + (2 * prob * auxilaryHash(key)) + (3*prob*prob))%maxSize;
    }

    bool find(string key){

        //for linked list

        if(linkedList){
            int index = countWeight(key) % maxSize;
            Node * temp = table[index];

            if(temp == NULL ) return false;
            else{
                while(temp != NULL){
                    if(temp->key == key) return true;
                    temp = temp->next;
                }
                return false;
            }
        }

        // for doubleHashing 

        else if(doubleHasing){
            int index = doubleHash(key,0);
            int i = 0;
            while(i < maxSize){
                if(table[index] == NULL){
                    i++;
                    index = doubleHash(key,i);
                    continue;
                }
                else if(table[index]->key == key){
                    return true;
                }
                i++;
                index = doubleHash(key,i);
            }
            return false;
        }

        //for custom Prob

        if(customProbing){
            int index = customProbe(key,0);
            int i = 0;
            while(i < maxSize){
                if(table[index] == NULL){
                    i++;
                    index = customProbe(key,i);
                    continue;
                }
                else if(table[index]->key == key){
                    return true;
                }
                i++;
                index = customProbe(key,i);
            }
            return false;
        }

    }

    void deleteNode(string key){

        NodeCounter--;

        // for linked list

        if(linkedList){
            int index = countWeight(key) % maxSize;
            int headConfirm = 0;
            Node * temp = table[index];

            if(temp == NULL ) return;
            else{
                while(temp != NULL){
                    if(temp->key == key) {
                        if(headConfirm == 0){
                            table[index] = table[index]->next;
                        }
                        else{
                            Node * temp2 = table[index];

                            while(temp2->next != temp){
                                temp2 = temp2->next;
                            }

                            temp2->next = temp->next;
                        }
                        return;
                    }
                    temp = temp->next;
                    headConfirm++;
                }
                return ;
            }
        }

        // for doubleHashing 

        else if(doubleHasing){
            int index = doubleHash(key,0);
            int i = 0;
            while(i < maxSize){
                if(table[index] == NULL){
                    i++;
                    index = doubleHash(key,i);
                    continue;
                }
                else if(table[index]->key == key){
                    table[index] = NULL;
                    return;
                }
                i++;
                index = doubleHash(key,i);
            }
        }

        //for custom Prob

        else if(customProbing){
            int index = customProbe(key,0);
            int i = 0;
            while(i < maxSize){
                if(table[index] == NULL){
                    i++;
                    index = customProbe(key,i);
                    continue;
                }
                else if(table[index]->key == key){
                    table[index] = NULL;
                    return;
                }
                i++;
                index = customProbe(key,i);
            }
        }

    }

    int numberOfCollision(){
        int collisionNumber = 0;
        for(int i = 0;i<maxSize;i++){
            if(table[i]!=NULL){
                Node * temp = table[i];
                while(temp!=NULL){
                    collisionNumber+=temp->collision;
                    temp = temp->next;
                }
            }
        }
        return collisionNumber;
    }

    double averageProbes(){
        double averageProbesNumber = 0;
        for(int i = 0;i<maxSize;i++){
            if(table[i]!=NULL){
                Node * temp = table[i];
                while(temp!=NULL){
                    averageProbesNumber+=temp->prob;
                    temp = temp->next;
                }
            }
        }
        return averageProbesNumber/double(NodeCounter);
    }

    void rehash(int c){
        if(c < MaximumChainLenght()){
            int lastIndex = maxSize;
            maxSize = originalSizeOfHashTable(maxSize*2);
            
            HashTable * temp = new HashTable(maxSize);
            temp->linkedList = true;
            temp->Hash_one_1 = this->Hash_one_1;
            temp->Hash_two_2 = this->Hash_two_2;
            for(int i = 0;i<lastIndex;i++){
                if(table[i] != NULL){
                    Node * temp2 = table[i];
                    while(temp2!= NULL){
                        temp->insert(temp2->key,temp2->value);
                        temp2 = temp2->next;
                    }
                }

            }
            table = temp->table;
        }
        if(c > MaximumChainLenght()){
            int lastIndex = maxSize;
            maxSize = originalSizeOfHashTable(maxSize/2);
            HashTable * temp = new HashTable(maxSize);
            temp->linkedList = true;
            temp->Hash_one_1 = this->Hash_one_1;
            temp->Hash_two_2 = this->Hash_two_2;
            for(int i = 0;i<lastIndex;i++){
                if(table[i] != NULL){
                    Node * temp2 = table[i];
                    while(temp2!= NULL){
                        temp->insert(temp2->key,temp2->value);
                        temp2 = temp2->next;
                    }
                }

            }
            table = temp->table;
        }
    }

    int MaximumChainLenght(){
        int checker = INT_MIN;
        int checker2 = 0;

        for(int i = 0;i<maxSize;i++){
            if(table[i]!=NULL){
                Node * temp = table[i];
                while(temp!=NULL){
                    checker2 += 1;
                    temp = temp->next;
                }
            }
            if(checker2 > checker){
                checker = checker2;
            }
            checker2 = 0;
        }
        return checker;
    }

    double loadFactor(){
        return double(NodeCounter)/double(maxSize);
    }

};

string wordGenerator(int length){
    string s = "";
    while(length--){
        s += ('a'+rand()%26);
    }
    return s;
}

int main(){
    
    
    int n;cin>>n;
    int l ;cin>>l;
    n = originalSizeOfHashTable(n);
    HashTable myTable(n);
    myTable.linkedList = true;
    myTable.Hash_one_1 = true;
    int counter = 0;

    while(n--){
        counter++;
        string s ;
        cin>>s;
        myTable.insert(s,counter);
    }

    cout<<endl;
    
    vector<string> s = myTable.reverse_compl();
    for(int i = 0;i<s.size();i+=2){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    for(int i = 1;i<s.size();i+=2){
        cout<<s[i]<<" ";
    }

    return 0;
}