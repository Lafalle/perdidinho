#include <vector>
#include <cstddef>
#include <functional>
#include <iostream>
#include <random>
#include <chrono>

using std::hash;
using std::vector;

template <typename HashedObj>
class HashTable {
    public:
        explicit HashTable(int size = 10007) : array(nextPrime(size)) { 
            makeEmpty(); //Cria uma tabela hash marcada como vazia
            }
            
        bool contains(const HashedObj & x) const { 
            return isActive(findPos(x)); //Verifica pelo elemento x na tabela hash ativa
            }
            
        void makeEmpty( ) {
            currentSize = 0; //Inicializa com o tamanho atual de 0
            
            for (auto & entry : array ) {
                entry.info = EMPTY; //Marca todos os compartimentos como vazios
            }
        }
        
        bool insert(const HashedObj & x) {
            int currentPos = findPos(x); //Verifica se o elemento x está presente como ativo
            
            if (isActive(currentPos)) {
                return false; //Retorna falso se já estiver ativo
            }
            
            array[currentPos].element = x; //Insere o elemento x
            array[currentPos].info = ACTIVE; //Marca o elemento x como ativo
            
            if (++currentSize > array.size() / 2) {
                rehash(); //Caso o fator de carga exceda 50%, redimensiona a tabela
            }
            
            return true; //Retorna verdadeiro se inserção foi bem sucedida
        }
        
        bool remove(const HashedObj & x) {
            int currentPos = findPos(x); //Verifica se o elemento x está presente como ativo
            
            if (!isActive(currentPos)) {
                printf("Número não encontrado na Hash.\n");
                return false; //Retorna falso se não está ativo
            }
            
            printf("Elemento %d encontrado e removido.\n", array[currentPos].element);
            array[currentPos].info = DELETED; //Marca o elemento x como excluido
            
            return true; //Retorna verdadeiro se remoção foi bem sucedida
        }
        
        enum EntryType {ACTIVE, EMPTY, DELETED};
        
        int findPos(const HashedObj & x) const { 
            int offset = 1;
            int currentPos = myhash(x);
            
            while (array[currentPos].info != EMPTY && array[currentPos].element != x) { //Procura pela posição disponivel para inserir o elemento x
                currentPos += offset; //Computa a próxima posição usando colisão quadrática
                offset += 2; //Incrementa o deslocamento para a próxima tentativa de busca
                
                if (currentPos >= array.size()) {
                    currentPos -= array.size(); //Caso a posição atual supere o tamanho total, subtraimos o tamanho para retorna ao começo
                }
            }
            
            
            return currentPos; //Retorna a posição em que inserir o elemento ou a posição onde o elemento foi encontrado
        }
        
    private:
        struct HashEntry {
            HashedObj element;
            EntryType info;
            HashEntry(const HashedObj & e = HashedObj{}, EntryType i = EMPTY)
                : element{e}, info{i}{}
            HashEntry(HashedObj && e, EntryType i = EMPTY)
                : element{std::move(e)}, info{i} {}
        };
        
        vector<HashEntry> array;
        int currentSize;
        
        bool isActive(int currentPos) const {
            return array[currentPos].info == ACTIVE; //Verifica se o compartimento solicitado está ativo
        }
        
        void rehash() {
            vector<HashEntry> oldArray = array;
            
            array.resize(nextPrime(2 * oldArray.size())); //Cria uma nova tabela vazia, com dobro do tamanho
            for (auto & entry : array) {
                entry.info = EMPTY;
            }
            
            currentSize = 0;
            for (auto & entry : oldArray) { //Copia tabela antiga para a nova
                if(entry.info == ACTIVE) {
                    insert(std::move(entry.element));
                }
            }
        }
        
        size_t myhash( const HashedObj & x ) const {
            static hash<HashedObj> hf;
            return hf(x) % array.size(); // Aplica a função de hash ao elemento x e retorna o índice correspondente
        }
        
        bool isPrime(int num) {
            if (num <= 1) {
                return false;
            }
            
            for (int i = 2; i * i <= num; ++i) {
                if (num % i == 0) {
                    return false;
                }
            }
            
        return true;
        }
        
        int nextPrime(int num) {
            while (!isPrime(num)) {
                ++num;
            }
            
        return num;
        }
};


// int main() {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     // Crie uma distribuição uniforme para gerar números inteiros entre um intervalo
//     std::uniform_int_distribution<int> dist(1, 100000);
    
//     HashTable<int> tabela;
//     auto startTime = std::chrono::high_resolution_clock::now();
    
//     // Insira números aleatórios na tabela hash
//     for (int i = 0; i <= 100000; ++i) {
//         //int num = dist(gen);  // Gera um número aleatório usando o gerador e a distribuição
//         tabela.insert(i);
//     }
    
//     // for (int i = 0; i <= 100000; ++i) {
//     //     int num = dist(gen);  // Gera um número aleatório usando o gerador e a distribuição
//     //     tabela.remove(num);
//     // }
    
//     // Verifique se um número específico está presente na tabela hash
//     auto startTimeContains = std::chrono::high_resolution_clock::now();
//     // for (int i = 0; i <= 100000; i++) {
//     int num = dist(gen);  // Gera um número aleatório usando o gerador e a distribuição
        
//     if (tabela.contains(num)) {
//              std::cout << "A tabela contem o numero " << num << std::endl;
//          } else {
//              std::cout << "A tabela nao contem o numero " << num << std::endl;
//          }
    
    
//     auto endTimeContains = std::chrono::high_resolution_clock::now();
//     auto durationContains = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeContains - startTimeContains);
//     std::cout << "Tempo de busca: " << durationContains.count() << " nanossegundos" << std::endl;

//     auto endTime = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
//     std::cout << "Tempo total: " << duration.count() << " nanossegundos" << std::endl;
//     return 0;
// }
