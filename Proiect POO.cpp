#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstring>
#include <sstream>

using namespace std;
class ManipulareFisier {
public: 
    virtual void manipuleazaFisier(const string& numeFisier) = 0;
    virtual ~ManipulareFisier() {}
};
class CitireFisierTxt : public ManipulareFisier {
protected:
    queue<char> ecuatii; // Membru protejat pentru a stoca caracterele ecuațiilor

public:
	CitireFisierTxt() : ecuatii() { }
    void manipuleazaFisier(const string& numeFisier) override {
        //cout << "Aceasta este implementarea din clasa CitireFisierTxt." << endl;
        cout << "Citeste fisierul: " << numeFisier << endl;

        // Deschide fișierul pentru citire
        ifstream fisier(numeFisier);

        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului de citire." << endl;
            return;
        }

        string linie;
        while (getline(fisier, linie)) {
            //cout << "Citita linie: " << linie << endl;
            // Adauga fiecare caracter din linie în coadă
            for (char caracter : linie) {
                ecuatii.push(caracter);
                //cout << caracter;//REZOLVARE
            }
            // Adauga un caracter de final de linie pentru a separa ecuatiile în coada
            ecuatii.push('\n');
            //cout << endl;
        }

        // Închide fișierul
        fisier.close();

        cout << "Citire fisier finalizata." << endl;
    }
    void afiseazaEcuatii() {
		queue<char> aux = ecuatii;
        while (!aux.empty()) {
            cout << aux.front(); // Afiseaza primul element din coada
            aux.pop(); // Elimina primul element din coada
        }
        cout << endl;
    }
    // Metodă pentru a accesa coada din exteriorul clasei
    const queue<char>& getEcuatiiQueue() const {
        return ecuatii;
    }
    ~CitireFisierTxt() {}
};

class CitireRezultateBinar : public ManipulareFisier {
public:
    void manipuleazaFisier(const string& numeFisier) override {
        ifstream rezultateBinar(numeFisier, ios::binary);

        if (!rezultateBinar.is_open()) {
            cerr << "Eroare la deschiderea fisierului binar de rezultate." << endl;
            return;
        }

        while (true) {
            // Citeste dimensiunea ecuației
            size_t ecuatieSize;
            rezultateBinar.read(reinterpret_cast<char*>(&ecuatieSize), sizeof(size_t));

            if (rezultateBinar.eof()) {
                break;
            }

            // Citeste ecuația
            string ecuatie(ecuatieSize, ' ');
			rezultateBinar.read(&ecuatie[0], ecuatieSize);//de interesat 

            // Citeste rezultatul
            double rezultat;
            rezultateBinar.read(reinterpret_cast<char*>(&rezultat), sizeof(double));//de interesat

            // Afișează ecuația și rezultatul
            cout << "Ecuatie: " << ecuatie << " | Rezultat: " << rezultat << endl;
        }

        rezultateBinar.close();
    }
};





class Sir {
protected:
    char* sir;
    bool valid;
    char* stivaChar;
    double* stivaDouble;
    int charCount, doubleCount;
    friend class Calculator;
public:
    Sir(){
        sir = new char[1];
        sir[0] = '\0';
        valid = true;
        this->stivaDouble = new double[0];
        this->stivaChar = new char[1];
        this->stivaChar[0] = '\0';
        charCount = 0;
        doubleCount = 0;
    }
    Sir(char* sir) {
        if (sir != nullptr) {
            this->sir = new char[strlen(sir) + 1];
            strcpy_s(this->sir, strlen(sir) + 1, sir);
            valid = true;
            this->stivaDouble = new double[0];
            this->stivaChar = new char[1];
            this->stivaChar[0] = '\0';
            
        }
        else {
            this->sir = new char[1];
            this->sir[0] = '\0';
        }
    }
    ~Sir() {
        delete[] sir;
        this->sir = nullptr;
        delete[] stivaChar;
        delete[] stivaDouble;

    }
    char* getSir() {
        return sir;
    }
    bool getValid() {
        return valid;
    }
    char* getStivaChar() {
        return stivaChar;
    }
    int getCharCount() {
        return charCount;
    }
    
    double* getStivaDouble() {
        return stivaDouble;
    }
    int getDoubleCount() {
        return doubleCount;
    }
    void Validare() {
        bool valid = true;
        //folosesc metoda lumanarii pentru a verifica daca am paranteze care nu se inchid
        int paranthesisCounter = 0;
        int paranthesisCounter2 = 0;
        
        //cout << "Lungimea sirului e de " << strlen(sir) << endl;
        for (int i = 0; i < strlen(sir); i++) 
        {
            
            char ch = sir[i];
            if (i == 0 || i == strlen(sir)) 
            {
                if (ch != '[' && ch != ']' && ch!='('&& ch!=')'&& !isdigit(ch)) {//ver daca primul sau ultimul  element sunt numar sau paranteze
                    valid = false;
                    cout << "primul sau ultimul caracter nu sunt numar sau paranteze"<<endl;
                    
                }
                if (i == 0 &&( ch == ')' || ch==']')) {
                    valid = false;
                    cout << "primul caracter e ')'sau ']'" << endl;
                }
                if (i == strlen(sir) - 1 && (ch == '(' || ch=='[')) {
                    valid = false;
                    cout << "ultimul caracter e '(' sau ']'" << endl;
                }
                if (i == 0 && ch == '(') {
                    paranthesisCounter++;
                }
                if (i == 0 && ch == '[') {
                    paranthesisCounter2++;
                }
                if (i == strlen(sir) - 1 && ch==')')
                {
                    paranthesisCounter--;
                }
                if (i == strlen(sir) - 1 && ch == ']')
                {
                    paranthesisCounter2--;
                }
                if (i == 0 && ch == '-') {// DE TESTAT
                    if (sir[i + 1] != '[' && sir[i + 1] != '(' && !isdigit(sir[i+1])) {
                        cout << "Dupa primul minus nu e un nr sau o paranteza" << endl;
                    }
                }

            }else{
                
                if(ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != '^' && ch != '#'&& ch != '(' && ch != ')' && ch != '.' && ch != '[' && ch != ']'&& ch != ' ' && !isdigit(ch))
                {
                    valid = false;
                    cout << "Exista caractere nepermise in sir"<<endl;
                    break;
                }
                if (ch == '(' || ch=='[')
                {
                    if(ch=='(')
                     paranthesisCounter++;
                    if (ch == '[')
                    {
                        paranthesisCounter2++;
                        if (paranthesisCounter > 0) {
                            cout<<"Sunt paranteze drepte in paranteze rotunde" << endl;
                            valid = false;

                        }
                    }
                    if (isdigit(sir[i - 1])) {
                        cout << "este un nr inainte de '('"<<endl;
                        valid = false;

                    }
                    if (sir[i - 1] == ')' || sir[i - 1] == ']') {
                        cout << "nu are voie sa fie )("<<endl;
                        valid = false;
                    }
                    // if (sir[i-1] != '*' && sir[i - 1] != '/' && sir[i - 1] != '+' && sir[i - 1] != '-' && sir[i - 1] != '^' && sir[i - 1] != '#')
            
                    if (sir[i + 1] == ')'|| sir[i + 1] == ']') {
                        cout << "apare o structura de forma ()"<<endl;
                        valid = false;
                    }
                    if (sir[i + 1] == '*' || sir[i + 1] == '+' || sir[i + 1] == '/' || sir[i + 1] == '^' || sir[i + 1] == '#') {
                        cout << "e un operator dupa '('"<<endl;
                        valid = false;
                    }
                }
                if (ch == ')'|| ch==']')
                {
                    if (ch == ')')
                        paranthesisCounter--;
                    if (ch == ']')
                    {
                        paranthesisCounter2--;
                        if (paranthesisCounter2 < 0) {
                            cout << "Sunt sunt prea multe paranteze inchise patrate]" << endl;
                            valid = false;

                        }
                    }
                    if (paranthesisCounter < 0) {
                        cout << "sunt prea multe paranteze inchise)"<<endl;
                        valid = false;
                    }
                
                    if (isdigit(sir[i + 1])) {
                        cout << "este un nr dupa ')'"<<endl;
                        valid = false;

                    }
                    if (sir[i + 1 ] == '(') {
                        cout << "nu are voie sa fie )("<<endl;
                        valid = false;
                    }
                        // if (sir[i-1] != '*' && sir[i - 1] != '/' && sir[i - 1] != '+' && sir[i - 1] != '-' && sir[i - 1] != '^' && sir[i - 1] != '#')
               
                    if (sir[i - 1] == '*' || sir[i - 1] == '+' || sir[i - 1] == '/' || sir[i - 1] == '^' || sir[i - 1] == '#') {
                        cout << "e un operator inainte de ')' sau ']'"<<endl;
                        valid = false;
                    }


                }
                if (ch == '*' || ch == '/' || ch == '+' || ch == '^' || ch == '#') {
                    if (!isdigit(sir[i - 1]) && sir[i - 1] != ')' && sir[i - 1] != ']') {
                        cout << "Inainte nu e un nr sau o paranteza ')'" << endl;
                        valid = false;
                    }
                    if (!isdigit(sir[i +1]) && sir[i + 1] != '(' && sir[i + 1] != '[') {
                        cout << "Dupa nu e un nr sau o paranteza '('" << endl;
                        valid = false;
                    }
                }
                if (ch == '.') {
                    if (!isdigit(sir[i - 1]) || !isdigit(sir[i + 1])) {
                        cout << ". nu e inauntrul unui nr";
                        valid = false;
                    }
                }
                if (ch == '-') {// DE TESTAT
                    if (!isdigit(sir[i - 1]) && sir[i - 1] != ')' && sir[i - 1] != '(' && sir[i - 1] != ']' && sir[i - 1] != '[') {
                        cout << "inainte de - nu e ce trebuie";
                        valid = false;
                    }
                    if (!isdigit(sir[i + 1]) && sir[i + 1] != '(' && sir[i + 1] != '[') {
                        cout << "dupa  -' nu e ce trebuie";
                        valid = false;
                    }
                }
            }
        }
        if (paranthesisCounter != 0) {
            cout << "Parantezele nu sunt deschise in mod egal" << endl;
            valid = false;
        }
        if (paranthesisCounter2 != 0) {
            cout << "Parantezele patrate nu sunt deschise in mod egal" << endl;
            valid = false;
        }
        //cout << "Valoarea validarii: " << valid << endl;
        
    }
    void eliminareSpatii() {
        int indexNou = 0;
        int dimensiune = strlen(sir);
        char* copie = new char[dimensiune + 1];
        for (int i = 0; i <= dimensiune; i++)
        {
            if (sir[i] != ' ') {
               
                copie[indexNou] = sir[i];
                indexNou++;
            }
        }
        strcpy_s(sir, dimensiune+1, copie);
        delete[] copie;
        copie = nullptr;

       
    }
    double convertToDouble(int& i) {
        double rezult = 0.0;
        int sign = 1;

        if (sir[i] == '-') {
            sign = -1;
            i++;
        }

        while (sir[i] >= '0' && sir[i] <= '9') {
            rezult = rezult * 10.0 + (sir[i] - '0');
            i++;
        }
        if (sir[i] == '.') {
            double fraction = 0.1;
            i++;
            while (sir[i] >= '0' && sir[i] <= '9' && sir[i] != '\0') {
                rezult = rezult + (sir[i] - '0') * fraction;
                fraction *= 0.1;
                i++;
            }
        }
        i--;
        rezult *= sign;
        return rezult;
    }
    

    void Parse() {
        if (this->stivaChar != nullptr) {
            delete[] stivaChar;
            stivaChar = nullptr;
        }
        if (this->stivaDouble != nullptr) {
            delete[] stivaDouble;
            stivaDouble = nullptr;
        }

        int length = strlen(sir);
        stivaChar = new char[length];
        stivaDouble = new double[length];
        charCount = 0, doubleCount=0;


        for (int i = 0; i < length; i++) {
            char currentChar = sir[i];
            if (isdigit(currentChar) || (currentChar == '-' && (sir[i - 1] == '(' || sir[i - 1] == '['))) {//qici s-ar putea sa fie eroarea  )
                stivaDouble[doubleCount] = this->convertToDouble(i);
                doubleCount++;
            }
            else {
                stivaChar[charCount] = sir[i];
                charCount++;
                
            }
        }
    }
    void setSir(const char* newSir) {
        // Eliberează memoria alocată pentru sirul curent
        delete[] sir;

        // Alocă memorie pentru noul sir și copiază-l
        sir = new char[strlen(newSir) + 1];
        strcpy_s(sir, strlen(newSir) + 1, newSir);

        // Resetează stivele și conteoarele
        delete[] stivaChar;
        delete[] stivaDouble;

        stivaChar = new char[strlen(sir)];
        stivaDouble = new double[strlen(sir)];
        charCount = 0;
        doubleCount = 0;

        // Reinițializează validarea, elimină spațiile și face parsing la noul sir
        valid = true;
        eliminareSpatii();
        
		Validare();
        if (valid == true) {
            Parse();
        }
    }
    void serialize(ofstream& out) const {
        size_t lungime = strlen(sir);
        out.write(reinterpret_cast<const char*>(&lungime), sizeof(size_t));
        out.write(sir, lungime);
    }

    void deserialize(ifstream& in) {
        delete[] sir;

        size_t lungime;
        in.read(reinterpret_cast<char*>(&lungime), sizeof(size_t));

        sir = new char[lungime + 1];
        in.read(sir, lungime);
        sir[lungime] = '\0';
    }
};

  
//Stack de double
class DoubleStack {
private:
    double* arr;
    int top;
    int maxSize;
    friend class Calculator;
public:
    DoubleStack() {
        maxSize = 999;
        top = -1;
        arr = new double[1];
        arr[0] = 0;
    }
    DoubleStack(int size) :maxSize(size) {

        arr = new double[maxSize];
        top = -1;
    }

    DoubleStack(const DoubleStack& s) :maxSize(s.maxSize) {
        arr = new double[s.maxSize];
        top = s.top;
    }
    DoubleStack& operator=(DoubleStack& s) {
        if (this != &s) {
            delete[] arr;
            arr = nullptr;
        
            this->maxSize = s.maxSize;
            top = s.top;

            this->arr = new double[this->maxSize];
            for (int i = 0; i <= s.top; i++) {
                arr[i] = s.arr[i];
            }

        }
        return *this;
    }
    bool isEmpty() {
        return(top == -1);
    }
    bool isFull() {
        return (top == maxSize - 1);
    }
    DoubleStack& operator+=(double element) {
        if (!isFull()) {
            top++;
            arr[top] = element;
        }
        return *this;
    }
    DoubleStack& operator--() {
        DoubleStack copie = *this;
        if (!this->isEmpty()) {
            this->top--;
        }
        else { //cout << "e deja goal ca-n fotbal";
        }
        return copie;
    }
    DoubleStack operator--(int) {
        if (!isEmpty()) {
            top--;
        }
        else { //cout << "e deja goal ca-n fotbal"; 
        }
        return *this;
    }
    double operator[](int position) {
        return arr[position];

    }
    ~DoubleStack() {
        delete[] arr;
        arr = nullptr;
    }
    friend istream& operator>>(istream& in, DoubleStack& s);
    friend ostream& operator<<(ostream& out, DoubleStack& s);
};

ostream& operator<<(ostream& out, DoubleStack& s) {
    // out << "Dimensiunea maxima a matricei este: " << s.maxSize << endl;
    if (s.isEmpty())
    {
        out << "Stiva e goala" << endl;
    }
    else {
        for (int i = 0; i <=s.top; i++) { //aici e o eroare undeva
            out << s[i] << " ";
        }
    }
    if (s.isFull()) {
        out << endl << "Stiva este plina";
    }
    return out;
}
istream& operator>>(istream& in, DoubleStack& s) {
    cout << "Introduceti dimensiunea maxima";
    in >> s.maxSize;
    cout << "Introduceti nr de operanzi:";
    in >> s.top;
    if (s.arr != nullptr) {
        delete[] s.arr;
        s.arr = nullptr;
    }
    s.arr = new double[s.maxSize];
    for (int i = 0; i < s.top; i++) {
        cout << "indrod. el de pe pozitita " << i << ": ";
        in >> s.arr[i];
    }
    return in;

}


class CharStack {
private:
    char* arr;
    int top;
    int maxSize;
    friend class Calculator;

public:
    CharStack() {
        maxSize = 999;
        top = -1;
        arr = new char[1];

    }

    CharStack(int size) : maxSize(size) {
        arr = new char[maxSize];
        top = -1;
    }

    CharStack(const CharStack& s) : maxSize(s.maxSize) {
        arr = new char[s.maxSize];
        top = s.top;
        for (int i = 0; i <= s.top; i++) {
            arr[i] = s.arr[i];
        }
    }

    CharStack& operator=(const CharStack& s) {
        if (this != &s) {
            delete[] arr;
            arr = nullptr;
        
            this->maxSize = s.maxSize;
            top = s.top;

            this->arr = new char[this->maxSize];
            for (int i = 0; i <= s.top; i++) {
                arr[i] = s.arr[i];
            }
        }
        return *this;
    }

    bool isEmpty() const {
        return (top == -1);
    }

    bool isFull() const {
        return (top == maxSize - 1);
    }

    CharStack& operator+=(char element) {
        if (!isFull()) {
            top++;
            arr[top] = element;
        }
        return *this;
    }

    CharStack& operator--() {
        if (!isEmpty()) {
            top--;
        }
        else {
            cout << "Stack is already empty" << endl;
        }
        return *this;
    }

    CharStack operator--(int) {
        CharStack copy = *this;
        if (!isEmpty()) {
            top--;
        }
        else {
            cout << "Stack is already empty" << endl;
        }
        return copy;
    }

    char operator[](int position) const {
        return arr[position];
    }

    ~CharStack() {
        delete[] arr;
        arr = nullptr;
    }

    friend istream& operator>>(istream& in, CharStack& s);
    friend ostream& operator<<(ostream& out, const CharStack s);
};

ostream& operator<<(ostream& out, const CharStack s) {
    if (s.isEmpty()) {
        out << "Stack is empty" << endl;
    }
    else {
        for (int i = 0; i <= s.top; i++) { 
            out << s[i] << " ";
        }
    }
    if (s.isFull()) {
        out << endl << "Stack is full";
    }
    return out;
}

istream& operator>>(istream& in, CharStack& s) {
    cout << "Enter the maximum size: ";
    in >> s.maxSize;
    cout << "Enter the number of elements: ";
    in >> s.top;

    if (s.arr != nullptr) {
        delete[] s.arr;
        s.arr = nullptr;
    }

    s.arr = new char[s.maxSize];
    for (int i = 0; i <= s.top; i++) {
        cout << "Enter element at position " << i << ": ";
        in >> s.arr[i];
    }
    return in;
}

class Calculator {
protected:
    double rezultat;
    Sir expresie;
    DoubleStack ds;
    CharStack cs;
public:
    Calculator() :rezultat (0),ds(99),cs(99),expresie() {
   
    };
    Calculator(char* sir):expresie(sir),ds(99),cs(99){// vreau sa fac apel implicit pentru ds si cs sau fie goale la inceput
		//DE FACUT: ds (sir.lungime),cs(sir.lungime)
        rezultat = 69;
		expresie.eliminareSpatii();
        expresie.Validare();//asta va arata daca este valida sau nu expresie
        expresie.Parse();
    }
    char* getSir() {
        return expresie.getSir();
    }
    double getRezultat() {
        return rezultat;
    }
    int Precedence(char ch) {
        if (ch == '[' || ch == '(') return 0;//REZOLVare:0 IN LOC DE 7
        if (ch == '#') return 6;
        if (ch == '^') return 5;
        if (ch == '/') return 4;
        if (ch == '*') return 3;
        if (ch == '-') return 2;
        if (ch == '+') return 1;
        if (ch == ']' || ch == ')') return 7;//poate merge sa scot astea de aici,desi nu ar trebui sa faca o mare diferenta
    }
    
    double applyOperator(char op, double x, double n) {
        switch (op) {
        case '[': return n;
        case '(': return n;
        case '+': return x + n;
        case '-': return x - n;
        case '*': return x * n;
        case '/': return x / n;
        case '^': {
            return pow(x, n);
        }
        case '#': {
            if (x < 0) {
                cout << "Radacina de numar negativ" << endl;
                return -1.0;
            }

            return pow(x, 1.0 / n); // Utilizează pow pentru a calcula rădăcina
        }
        default: return 0.0;
        }
    }
    void setExpresie(char* newSir) {
        expresie.setSir(newSir);
        // Revalidează și reparsează noul sir
        expresie.eliminareSpatii();
        expresie.Validare();
        expresie.Parse();
    }
    void evaluateExpression() {
       // expresie.eliminareSpatii();//poate astea nu mai sunt folositoare
        //expresie.Validare();//poate astea nu mai sunt folositoare
        if (!expresie.valid) {
            cout << endl << "expresia nu este valida" << endl;
        }
        else {
            expresie.Parse();
            /*for (int i =0, int j = 0; i < expresie.charCount || j < expresie.doubleCount;) {
                if (expresie.stivaChar[i] == '[' || expresie.stivaChar[i] == '(') {
                    cs += expresie.stivaChar[i];
                }
                if()
            }*/
            int turn = 1;
            for (int i = 0,j=0; i < expresie.charCount ||  j<expresie.doubleCount; ) { // am modifcat ||  in && cum ar trebui si nu a mers dci e posibil sa fie ceva la stiva

               // cout <<endl<< "Processing: " << expresie.stivaChar[i] << endl;

                 if (expresie.stivaChar[i] == '(' || expresie.stivaChar[i] == '[' && turn == 1) {
                    // cout << "------------------------(" << endl;
                   // cout << "Pushing to cs: " << expresie.stivaChar[i] << endl;

                    cs += expresie.stivaChar[i];
                    i++;
                   // cout << cs<<endl;
                   // cout << ds << endl;
                }

                else if ((expresie.stivaChar[i] == ')' || expresie.stivaChar[i] == ']')&& turn == -1) {//REOLVARE: aplic ')' daca turn==-1, pt semne
                   //  cout << "------------------------)" << endl;
                     int ok = 1;
                        while (!cs.isEmpty() && cs.top != '('&& cs.top != '[' && ok==1) {
                            //if (cs.top != '(' || cs.top != '[') { ok = 0; }
                          //  cout << endl;
                            //cout << cs << endl;
                            //cout << ds << endl;
                            char op = cs[cs.top];
                                cs--;
                            double n = ds[ds.top];
                                ds--;
                            double x = ds[ds.top];
                            if   (op != '('&& op != '[')//REZOLVARE: daca operatorul e '(' nu scot 2 operanzi
                            {
                                ds--;
                            }

						    //cout << "Before applying ): " << x << " " << op << " " << n << endl;
                            
                            ds += applyOperator(op, x, n);
                            /*cout << endl;
					        cout << "After applying ): " << x << " " << op << " " << n << endl; 
                            cout << cs << endl;
                            cout << ds << endl;*/
                            if (op == '[' || op == '(') {
                                break;
                            }
                    }
                    //POATE NU AR TREBUI SA FIE AICIcs--; // Pop the '('
                        if (expresie.stivaChar[i + 1] == ')' || expresie.stivaChar[i + 1] == ']') {}
                        else { turn = -1; }
                    //-1  REZOLVARE: E VITAL
                    /*
                    cout << "Popping from cs: ')' " << endl;
					cout << cs << endl;
                    cout << ds << endl;*/
                    i++;
                }
                else if (turn == -1) {
                    //cout << "------------------------nou semn" << endl;
                    while (!cs.isEmpty() && Precedence(cs[cs.top]) >= Precedence(expresie.stivaChar[i])) {

                        /*cout << endl;
                        cout << cs << endl;
                        cout << ds << endl*/

                        char op = cs[cs.top];
                        cs--;
                        double n = ds[ds.top];
                        ds--;
                        double x = ds[ds.top];
                        ds--;
                        
                        //cout << "Before applying: " << x << " " << op << " " << n << endl;
                        ds += applyOperator(op, x, n);

                        /*cout << "After applying: " << x << " " << op << " " << n << endl;
                        cout << cs << endl;
                        cout << ds << endl;*/

                    }

                    cs += expresie.stivaChar[i];

                    /*cout << endl;
                    cout << "Pushing to cs: " << expresie.stivaChar[i] << endl;
                    cout << cs << endl;
                    cout << ds << endl;*/

                    turn *= -1;
                    i++;
                }else if (turn == 1) {
                    //cout << "------------------------nou numar" << endl;
                    //cout << "Pushing to ds: " << expresie.stivaDouble[j] << endl;
                    
                    ds += expresie.stivaDouble[j];//poate aici era problema
                    //cout << cs << endl;
                    //cout << ds << endl;
                    turn *= -1;
                    j++;
                }
                    
                
            }
           //cout << "------------------------final" << endl;
           while (!cs.isEmpty()) {
               /*
               cout << "------------------------facem operatii ramase" << endl;
               cout << "Inainte de operatie";
			   cout << endl;    
               cout << cs << endl;
               cout << ds << endl;
               */
               
                char op = cs[cs.top];
                cs--;
                double n = ds[ds.top];
                ds--;
                double x = ds[ds.top];
                ds--;
                ds += applyOperator(op, x, n);
                
                /*
                cout << endl;
                cout << "Dupa operatie" << endl;
                cout << cs << endl;
                cout << ds << endl;
                */
            }
           
             rezultat=ds[ds.top];
             if (rezultat == -0)
             {
                 rezultat = 0;
             }
               // ds--;
             //cout << "Rezultat final: " << rezultat << endl;
             ds--;
        }
    }
    
};



class RezultateFisierTxt : public Calculator, public CitireFisierTxt {
public:
    RezultateFisierTxt() : CitireFisierTxt(), Calculator() {
    }

    virtual void afiseazaRezultate(const string& numeFisier,const string& numeFisierRezultate) {
        manipuleazaFisier(numeFisier);
        ofstream rezultateFisier(numeFisierRezultate);

        if (!rezultateFisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului de rezultate." << endl;
            return;
        }

        while (!ecuatii.empty()) {
            string ecuatie = extrageEcuatie();
            //setExpresie(&ecuatie[0]);//IN LOC DE ecuatie.c_str()
            setExpresie(&ecuatie[0]);
            evaluateExpression();
            rezultateFisier << "Ecuatia: " << ecuatie << endl;
            rezultateFisier << "Rezultatul: " << getRezultat() << endl << endl;
        }

        rezultateFisier.close();
        cout << "Rezultatele au fost scrise in fisierul " << numeFisierRezultate << endl;
    }
    ~RezultateFisierTxt()
    {
      
    }
protected:
    string extrageEcuatie() {
        stringstream ss;//de interesat
        char caracter;
        while (!ecuatii.empty() && (caracter = ecuatii.front()) != '\n') {
            ss << caracter;
            ecuatii.pop();
        }
        // Extragem si '\n' de la sfarsitul ecuatiei
        ecuatii.pop();
        return ss.str();//AICI IMI DA BREAKPOINT
    }

};

class RezultateFisierBinar : public RezultateFisierTxt {
public:
    RezultateFisierBinar() : RezultateFisierTxt(){
        
    }

    void afiseazaRezultate(const string& numeFisier,const string& numeFisierRezultateBinar) {
        manipuleazaFisier(numeFisier);
        ofstream rezultateBinar(numeFisierRezultateBinar, ios::binary);

        if (!rezultateBinar.is_open()) {
            cerr << "Eroare la deschiderea fisierului binar de rezultate." << endl;
            return;
        }

        while (!ecuatii.empty()) {
            string ecuatie = extrageEcuatie();
            setExpresie(&ecuatie[0]);  // IN LOC DE ecuatie.c_str()
            evaluateExpression();

            // Scrie ecuatia sub formă binară
            size_t ecuatieSize = ecuatie.size();
            rezultateBinar.write(reinterpret_cast<const char*>(&ecuatieSize), sizeof(size_t));
            rezultateBinar.write(ecuatie.c_str(), ecuatieSize);

            // Scrie rezultatul sub formă binară
            double rezultat = getRezultat();
            rezultateBinar.write(reinterpret_cast<const char*>(&rezultat), sizeof(double));
        }

        rezultateBinar.close();
        cout << "Rezultatele au fost scrise in fisierul binar " << numeFisierRezultateBinar << endl;
    }
};

class Meniu {
public:
    virtual void executa() = 0; // Funcție pur virtuală pentru a executa opțiunea
};
class Optiune1 : public Meniu {
public:
    void executa() override {
        // Implementarea pentru opțiunea 1
        // Preia ecuațiile dintr-un fsier de ecuatii și pune rezultatele în fisierul text de rezolvari
        string numeFisierTextRezultate;
		string numeFisierEcuatii;
		cout << "Introduceti numele fisierului de ecuatii: "; 
		cin >> numeFisierEcuatii;
		cout << "Introduceti numele fisierului text de rezultate: ";
		cin >> numeFisierTextRezultate;
        RezultateFisierTxt rezultate;
        rezultate.afiseazaRezultate(numeFisierEcuatii, numeFisierTextRezultate);

    }
};
class Optiune2 : public Meniu {
public:
    void executa() override {
        // Implementarea pentru opțiunea 2
        // Preia ecuațiile din fișierul text și pune rezultatele în fișierul binar de rezolvări
        string numeFisierBinarRezultate;
        string numeFisierEcuatii;
        cout << "Introduceti numele fisierului de ecuatii: ";
        cin >> numeFisierEcuatii;
        cout << "Introduceti numele fisierului binar de rezultate: ";
        cin >> numeFisierBinarRezultate;
        RezultateFisierBinar rezultate;
        rezultate.afiseazaRezultate(numeFisierEcuatii, numeFisierBinarRezultate);
    }
};
class Optiune3 : public Meniu {
public:
    void executa() override {
        // Implementarea pentru opțiunea 3
        // Vizualizează conținutul fișierului text cu rezultate
        CitireFisierTxt cititor;
		string numeFisierText;
		cout << "Introduceti numele fisierului text cu rezultate: ";
		cin >> numeFisierText;
		cititor.manipuleazaFisier(numeFisierText);
        cititor.afiseazaEcuatii();
    }
};
class Optiune4 : public Meniu {
public:
    void executa() override {
        // Implementarea pentru opțiunea 4
        // Vizualizează conținutul fișierului binar cu rezultate
        CitireRezultateBinar citireRezultateBinar;
        string numeFisierBinarRezultate ;
        cout << "Introduceti numele fisierului binar de rezultate: ";
        cin >> numeFisierBinarRezultate;

        citireRezultateBinar.manipuleazaFisier(numeFisierBinarRezultate);
    }
};
class Optiune5 : public Meniu {
public:
    void executa() override {
        char buffer[100];

        cout << "Introduceti ecuatia: ";
        cin.get();//REZOLVARE :aici asa trebui 
        cin.getline(buffer, sizeof(buffer));

        Sir ecuatie(buffer);
        ecuatie.Validare();
        if(ecuatie.getValid()!=0)
        {
            Calculator calculator(buffer);

            cout << "Ecuatia introdusa: " << calculator.getSir() << endl;

            calculator.evaluateExpression();
            cout << "Rezultatul expresiei este: " << calculator.getRezultat() << endl;
			
            char raspuns[5];
            cout << "Doriti sa salvati ecuatia si rezultatul? (da/nu): ";
            cin.getline(raspuns, sizeof(raspuns));

            if (strcmp(raspuns, "da") == 0) {
                string numeFisierEcuatii;
                cout << "Introduceti numele fisierului de ecuatii: ";
                cin >> numeFisierEcuatii;
                // Salveaza in fisierul text de ecuatii
                ofstream fisierText(numeFisierEcuatii, ios::app);
				fisierText << endl;
                fisierText << ecuatie.getSir() ;
                fisierText.close();

                string numeFisierTextRezultate;

                cout << "Introduceti numele fisierului text de rezultate: ";
                cin >> numeFisierTextRezultate;
                RezultateFisierTxt rezultate;
                rezultate.afiseazaRezultate(numeFisierEcuatii, numeFisierTextRezultate);


                string numeFisierBinarRezultate;

               
                cin >> numeFisierEcuatii;
                cout << "Introduceti numele fisierului binar de rezultate: ";
                cin >> numeFisierBinarRezultate;
                RezultateFisierBinar rezultate2;
                rezultate2.afiseazaRezultate(numeFisierEcuatii, numeFisierBinarRezultate);



                /*// Salveaza in fisierul text de rezultate
                ofstream fisierRezultate("rezultate.txt", ios::app);
                fisierRezultate << calculator.getRezultat() << endl;
                fisierRezultate.close();

                // Salveaza in fisierul binar de rezultate
                ofstream fisierBinar("rezolvari.bin", ios::binary | ios::app);
                ecuatie.serialize(fisierBinar);

                double rezultat = calculator.getRezultat();
                fisierBinar.write(reinterpret_cast<char*>(&rezultat), sizeof(double));

                fisierBinar.close();*/

                cout << "Datele au fost salvate." << endl;
            }
        }
        else {
            cout << "Expresia nu e valida";
        }
        
    }
};

void afiseazaMeniu() {
    cout << endl;
    cout << "===== MENIU =====" << endl;
    cout << "1. Preia ecuatii din fisierul text de ecuatii si salveaza rezultatele in fisierul text de rezolvari." << endl;
    cout << "2. Preia ecuatii din fisierul text de ecuatii si salveaza rezultatele in fisierul binar de rezolvari." << endl;
    cout << "3. Vizualizare fisier text cu rezultate." << endl;
    cout << "4. Vizualizare fisier binar cu rezultate." << endl;
    cout << "5. Introducere ecuatie de la tastatura si afisare rezultat." << endl;
    cout << "0. Iesire." << endl;
    cout << "=================" << endl;
    cout << "Alege o optiune: ";
    cout << endl;

}
int main()
{
    int optiune;
    while (true) {
        afiseazaMeniu();
        cin >> optiune;
        //VIRTUALIZREA PARE NU OK
        Meniu* optiuneSelectata = nullptr;//aici cred CA AR TREBUI SA PUN NEW 

        switch (optiune) {
        case 1:
            optiuneSelectata = new Optiune1();
            break;
        case 2:
            optiuneSelectata = new Optiune2();
            break;
        case 3:
            optiuneSelectata = new Optiune3();
            break;
        case 4:
            optiuneSelectata = new Optiune4();
            break;
        case 5:
            optiuneSelectata = new Optiune5();
            break;
        case 0:
            cout << "La revedere!" << endl;
            return 0;
        default:
            cout << "Optiune invalida. Te rog sa alegi din nou." << endl;
            continue;
        }

        optiuneSelectata->executa();

        delete optiuneSelectata;
    }
    //RezultateFisierTxt rezultate("ecuatii.txt");
    //rezultate.afiseazaRezultate("rezolvari.txt");

    /*
    CitireFisierTxt cititor;
    cititor.manipuleazaFisier("ecuatii.txt");

	RezultateFisierTxt rezultate;
	rezultate.afiseazaRezultate("ecuatii.txt", "rezolvari.txt");

	RezultateFisierBinar rezultateBinar;
	rezultateBinar.afiseazaRezultate("ecuatii.txt", "rezolvari.bin");

    CitireRezultateBinar citireRezultateBinar;

    
     string numeFisierBinarRezultate = "rezolvari.bin";

    citireRezultateBinar.manipuleazaFisier(" rezolvari.bin");//numeFisierBinarRezultate


    
    char* sir = new char[100];
    cin.getline(sir, 100);
   
    Sir S1(sir);

    

    
    Calculator  c3(sir);
   
    cout << c3.getSir();
    
    c3.evaluateExpression();
    
    cout << endl << "Rezultatul expresiei este = " << c3.getRezultat();
    */
   


    //char* sCh = S1.getStivaChar();
    //double* sDb = S1.getStivaDouble();

 

   





    
    /* Sir Sir(sir);
    Sir.Parse();
    Calculator c1(sir);
    cout << c1.getSir();*/

    /*
    char* stivaChar= Sir.getStivaChar();
    double* stivaDouble=Sir.getStivaDouble();
    cout << endl;
    for (int i = 0; i < Sir.getCharCount(); i++) {
        cout << stivaChar[i]<<' ';
    }
    cout << endl;
    for (int i = 0; i < Sir.getDoubleCount(); i++) {
        cout << stivaDouble[i]<<' ';
    }
    */
    
   /* DoubleStack doubleStack(30);
    //cout << doubleStack;
    doubleStack += 10;
    doubleStack += 30;
    doubleStack += 32;
    doubleStack += 69; 
    doubleStack += 69;
    doubleStack += 18;
    doubleStack += 16;
    //cout << endl<< doubleStack<<endl;*/
    
   /* CharStack charStack(30);
    //cout << doubleStack;
    charStack += '*';
    charStack += '#';
    charStack += '+';
    charStack += '(';
    
    cout << endl << charStack << endl;*/
    
    
   /* DoubleStack dstack(Sir.getDoubleCount() + 10 + 1);
    dstack = doubleStack;
    cout << endl << dstack << endl;
    dstack += 23;
    cout << endl << dstack << endl;*/

    /*DoubleStack dstack2(Sir.getDoubleCount() + Sir.getCharCount() + 1);
    cin >> dstack2;
    cout << dstack2;*/
    //cout << dstack;


   // Sir.eliminareSpatii();
   // double number;
   // char* sirNou = new char [strlen(Sir.getSir())+1];
   // strcpy_s(sirNou, strlen(Sir.getSir()) + 1, Sir.getSir());
   // number = Sir.convertToDouble(Sir.getSir(), 0);
    /*int i = 0;

    number = Sir.convertToDouble(i);
    cout << endl << number;
    cout << endl << number + 1; 
    cout << endl << i;*/
   // delete[] sirNou;
   

    //Sir.Validare();
}

