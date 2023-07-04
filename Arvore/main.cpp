#include <iostream>
#include "arvoreRB.cpp"
#include "hash.cpp"
#include <chrono>

int main (){
    std::random_device rd;
    std::mt19937 gen(rd());
    // Crie uma distribuição uniforme para gerar números inteiros entre um intervalo
    std::uniform_int_distribution<int> dist(1, 10000);
    //std::uniform_int_distribution<long> dist2(1, 1000000);

    int num = dist(gen);
    HashTable<int> tabela;
    RedBlackTree arvore;
    
    
    auto startTimeHash = std::chrono::high_resolution_clock::now();
    // Insira números aleatórios na tabela hash
    for (int i = 0; i <= 1000000; i++) {
       int num = dist(gen);  // Gera um número aleatório usando o gerador e a distribuição
       tabela.insert(num);
    }
    auto endTimeHash = std::chrono::high_resolution_clock::now();
    auto durationHash = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeHash - startTimeHash);
    std::cout << "Tempo de inserção (de 1000000 itens) na Hash: " << durationHash.count() << " nanossegundos" << std::endl;
    
    
    startTimeHash = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= 1000000; i++) {
        long num = dist(gen);  // Gera um número aleatório usando o gerador e a distribuição
        
        if (tabela.contains(num)) {
            //std::cout << "A tabela contem o número " << num << std::endl;
        } 
        
        else {
            //std::cout << "A tabela nao contem o número " << num << std::endl;
        }
    }
    endTimeHash = std::chrono::high_resolution_clock::now();
    durationHash = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeHash - startTimeHash);
    std::cout << "Tempo de busca (por 1000000 itens) na Hash: " << durationHash.count() << " nanossegundos" << std::endl;
    
    
    auto startTimeTree = std::chrono::high_resolution_clock::now();
    // Insira números aleatórios na tabela hash
    for (int i = 0; i <= 1000000; ++i) {
       arvore.insert(i);
    }
    auto endTimeTree = std::chrono::high_resolution_clock::now();
    auto durationTree = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeTree - startTimeTree);
    std::cout << "Tempo de inserção (de 1000000 itens) na Árvore: " << durationTree.count() << " nanossegundos" << std::endl;
    
    
    startTimeTree = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= 1000000; i++) {
        int num = dist2(gen);  // Gera um número aleatório usando o gerador e a distribuição
        
        if (arvore.search(num)) {
            //std::cout << "A árvore contem o número " << num << std::endl;
        }
        
        else {
            //std::cout << "A árvore contem o número " << num << std::endl;
        }
    }
    endTimeTree = std::chrono::high_resolution_clock::now();
    durationTree = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeTree - startTimeTree);
    std::cout << "Tempo de busca (por 1000000 itens) na Árvore: " << durationTree.count() << " nanossegundos" << std::endl;


    return 0;
}
