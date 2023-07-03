#include <iostream>
#include "arvoreRB.cpp"
#include "hash.cpp"
#include <chrono>

int main (){
    std::random_device rd;
    std::mt19937 gen(rd());
    // Crie uma distribuição uniforme para gerar números inteiros entre um intervalo
    std::uniform_int_distribution<int> dist(1, 100000);

    int num = dist(gen);
    HashTable<int> tabela;
    RedBlackTree arvore;
    
    auto startTimeHash = std::chrono::high_resolution_clock::now();
    tabela.contains(num);
    auto endTimeHash = std::chrono::high_resolution_clock::now();
    auto durationHash = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeHash - startTimeHash);
    std::cout << "Tempo de busca na Hash: " << durationHash.count() << " nanossegundos" << std::endl;
    
    arvore.search(num);


    return 0;
}