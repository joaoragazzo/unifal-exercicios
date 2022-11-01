#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

struct veiculos{
    string modelo;
    string marca;
    string tipo;
    string ano;
    string km;
    string potencia;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    string portas;
    string placa;
    string preco;
};

void deletarVeiculo(veiculos *db[], int pos, int *index){
    while(db[pos+1]){
        db[pos] = db[pos+1];
        pos++;
    }

    db[pos] = db[pos+1];
    delete(db[pos+1]);
    db[pos+1] = NULL;
    *index = *index - 1;
}

void imprimirVeiculos(veiculos *db[], int index){
    for(int j = 0; j < index; j++){
        cout << "Carro posição (" << j << "): ";
        cout << db[j]->modelo << " ";
        cout << db[j]->marca << " ";
        cout << db[j]->tipo << " ";
        cout << db[j]->ano << " ";
        cout << db[j]->km << " ";
        cout << db[j]->potencia << " ";
        cout << db[j]->combustivel << " ";
        cout << db[j]->cambio << " ";
        cout << db[j]->direcao << " ";
        cout << db[j]->cor << " ";
        cout << db[j]->portas << " ";
        cout << db[j]->placa << " ";
        cout << db[j]->preco << endl;
    }
}

int encontrarVeiculo(veiculos *db[], int index, string placa_){
    for(int pos = 0; pos < index; pos++){
        if(db[pos]->placa == placa_){
            return pos;
        } else if (pos == index-1){
            cout << "\033[31mCarro inexistente\033[0m" << endl;
            return -1;
        }
    }
  return -1;
}

void inserirVeiculo(veiculos *db[], int *index){
    cout << "Digite as informações dos veículos que deseja inserir." << endl;
    string placa;

    cout << "Placa: ";
    cin >> placa;
    int i = encontrarVeiculo(db, *index, placa);
    
    if(i > 0){
        cout << "\033[31mCarro já existente no nosso banco de dados.\033[0m" << endl;
        return;
    }


    db[*index] = new veiculos;
    cout << "Modelo: ";
    cin >> db[*index]->modelo;
    cout << "Marca: ";
    cin >> db[*index]->marca;
    cout << "Tipo: ";
    cin >> db[*index]->tipo;
    cout << "Ano: ";
    cin >> db[*index]->ano;
    cout << "Km: ";
    cin >> db[*index]->km;
    cout << "Potencia: ";
    cin >> db[*index]->potencia;
    cout << "Combustível: ";
    cin >> db[*index]->combustivel;
    cout << "Câmbio: ";
    cin >> db[*index]->cambio;
    cout << "Direção: ";
    cin >> db[*index]->direcao;
    cout << "Cor: ";
    cin >> db[*index]->cor;
    cout << "Portas: ";
    cin >> db[*index]->portas;
    cout << "Preço: ";
    cin >> db[*index]->preco;

    db[*index]->placa = placa;


    //ADICIONAR O CARRO NOVO NO BANCO DE DADOS




    *index = *index + 1;
}

void dadosVeiculo(veiculos *db[], int pos){
    cout << "Dados do veículo na posição " << pos << ":" << endl;
    cout << "Modelo: " << db[pos]->modelo << endl;
    cout << "Marca: " << db[pos]->marca << endl;
    cout << "Tipo: "<< db[pos]->tipo << endl;
    cout << "Ano: "<< db[pos]->ano << endl;
    cout << "Km: "<< db[pos]->km << endl;
    cout << "Potencia: "<< db[pos]->potencia << endl;
    cout << "Combustivel: "<< db[pos]->combustivel << endl;
    cout << "Cambio: "<< db[pos]->cambio << endl;
    cout << "Direcao: "<< db[pos]->direcao << endl;
    cout << "Cor: "<< db[pos]->cor << endl;
    cout << "Portas: "<< db[pos]->portas << endl;
    cout << "Placa: "<< db[pos]->placa << endl;
    cout << "Preço: " << db[pos]->preco << endl;
}

int isNear(int price, int array[], int lenght){
    for(int i = 0; i < lenght; i++){       
        if(array[i] - price > 0)
            return i;
    }
}

void nearstPrices(veiculos *db[], int price, int lenght){
    int prices[lenght], index = 0,proximo = 0, overflow = 0, underflow = 0, m = 0, n = 0;

    for(int i = 0; i < lenght; i++){
        if(proximo < stoi(db[i]->preco)){
            prices[lenght - 1] = i;
            proximo = stoi(db[i]->preco);
        }
    }

    proximo = 0;

    for(int i = lenght - 2; i >= 0; i--){
        for(int j = 0; j < lenght - 1; j++){
            if(stoi(db[j]->preco) >= proximo && stoi(db[j]->preco) <= stoi(db[prices[i+1]]->preco) && prices[i+1] != j){
                proximo = stoi(db[j]->preco);
                index = j;
                cout << "Condição: " << db[j]->preco << ">=" << proximo << " E " << db[j]->preco << "<" << db[prices[i+1]]->preco << endl; 
            }
        }
        cout << "========================" << endl;
        prices[i] = index;
        proximo = 0;
        index = 0;
    }

    for(int i = 0; i < lenght; i++){
        cout << prices[i] << " - " << db[prices[i]]->preco << endl;
    }
}

void ordenarPlacas(veiculos *db[], veiculos *ordenado[], int length){
    string valorMaximo = "";
    int posicao;
    for(int i = 0; i < length; i++){
        if(db[i]->placa > valorMaximo){
            valorMaximo = db[i]->placa;
            posicao = i;
        }
    }

    ordenado[length-1] = db[posicao];
    valorMaximo = "";
    posicao = 0;

    for(int i = length - 1; i >= 0; i--){
        for(int j = 0; j < length; j++){
            if(db[j]->placa < ordenado[i]->placa && db[j]->placa >= valorMaximo){
                valorMaximo = db[j]->placa;
                posicao = j;
            }
        }

        ordenado[i-1] = db[posicao];

        valorMaximo = "";
        posicao = 0;
    }
}

int main(void){ 

    cout << "  __ _  __ _ _ __ __ _  __ _  ___ _ __ ___  \n / _` |/ _` | '__/ _` |/ _` |/ _ \\ '_ ` _ \\ \n| (_| | (_| | | | (_| | (_| |  __/ | | | | |\n \\__, |\\__,_|_|  \\__,_|\\__, |\\___|_| |_| |_|\n  __/ |                 __/ |               \n |___/                 |___/                \n" << endl;

    veiculos *db[50], *ordenado[50];
    int index = 0, pos, priceSearch;
    string option;
    bool ordenadoState = false;
    
    ifstream myFile("DB_Veiculos");

    string placa_;
    string opts1 = "\033[1mO que você deseja fazer? \033[0m(I)nserir, (C)onsulta, (F)inalizar, (B)anco de Dados, (P)reços, (O)rdenação => ";
    string opts2 = "\033[1mO que você deseja fazer?\033[0m (D)eletar, (I)formações, (C)orrigir, (F)inalizar => ";
    string foundPlaca = "\033[1mDigite o número da placa que você deseja encontrar:\033[0m ";
    string optNotFound = "\033[31mOpção não encontada. Por favor, tente novamente.\033[0m";

    if (myFile.is_open()) {
        while ( !myFile.eof() ) {
            db[index] = new veiculos;
            myFile >> db[index]->modelo;
            myFile >> db[index]->marca;
            myFile >> db[index]->tipo;
            myFile >> db[index]->ano;
            myFile >> db[index]->km;
            myFile >> db[index]->potencia;
            myFile >> db[index]->combustivel;
            myFile >> db[index]->cambio;
            myFile >> db[index]->direcao;
            myFile >> db[index]->cor;
            myFile >> db[index]->portas;
            myFile >> db[index]->placa;
            myFile >> db[index]->preco;
            index++;
        }

    for(int j = index; j < 50; j++){
        db[j] = NULL;
    }

    myFile.close();

    } else {
        cout << "\033[41mNão foi possível abrir o db\033[0m" << endl;
        return 0;
    } 
    
    while(option[0] != 'F'){

        cout << opts1; 
        cin >> option;

        while(option[0] != 'I' && option[0] != 'C' && option[0] != 'F' && option[0] != 'B' && option[0] != 'P' && option[0] != 'O'){
            cout << optNotFound << endl;
            cout << opts1;
            cin >> option;
        }

        if(option[0]=='C'){

            cout << foundPlaca;
            cin >> placa_;
            pos = encontrarVeiculo(db, index, placa_);

            while(pos < 0){
                cout << "Placa não encontrada no nosso sistema. Por favor, tente novamente." << endl;
                cout << foundPlaca;
                cin >> placa_;
                pos = encontrarVeiculo(db, index, placa_);
            }

            cout << "O que você deseja fazer com o veículo de placa " << placa_ << "? (D)eletar, (I)nformações, (F)inalizar => ";
            cin >> option;

            while(option[0] != 'D' && option[0] != 'I' && option[0] != 'M' && option[0] != 'C' && option[0] != 'F'){
                cout << optNotFound << endl;
                cout << opts2;
                cin >> option;
            }

            if (option[0]=='D'){
                deletarVeiculo(db, pos, &index);
                ordenadoState = false;
                continue;
            }

            if (option[0]=='I'){
                dadosVeiculo(db, pos);
                continue;
            }


        }

        if(option[0]=='I'){
            inserirVeiculo(db, &index);
            ordenadoState = false;
        }

        if(option[0]=='B'){
            imprimirVeiculos(db, index);
            continue;
        }
        
        if(option[0]=='P'){
            cout << "Por favor, digite o valor que você deseja receber os 10 valores mais proximos => ";
            cin >> priceSearch;

            nearstPrices(db, priceSearch, index);
        }

        if(option[0]=='O'){
            if(!ordenadoState){
                int indexSalvo = index;                                   //NÃO CONSEGUI DESCOBRIR O MOTIVO, MAS SEMPRE QUE O INDEX PASSA PELA FUNÇÃO
                ordenarPlacas(db, ordenado, index);                      //ORDENAR PLACAS, A VARIAVEL É PERDIDA E UM NUMERO ALEATÓRIO ASSUME O 
                index = indexSalvo;                                     //VALOR DA VARIAVEL.
                ordenadoState = true;
            }                                    
            imprimirVeiculos(ordenado, index);
            
        }
    }

    cout << "Saindo do algoritimo..." << endl;    
}
//adicionar inserção de veículos