/*
    Keywords:
    Rev -> Reverse
    D2 -> Draw 2
    D-4 -> Draw 4
    S -> Skip


    examples:
    S-R -> Skip Red
    R-9 -> Red 9
    D2B -> Draw 2 Blue
    Rev-Y -> Reverse Yellow

    


*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include<utility> // for the use of pairs to implement a map
#include <cstdlib> // For system()
#include<windows.h>
#include<limits>
using namespace std;
void SkipSpecial();
void Draw4Special();
void Draw2Special();
void ReverseSpecial();
void WildSpecial();
class Invalidinput:public exception{
    public:
    const char* what(){
        return "Invalid input";
    }
};
class Menu{
    public:
    const vector<string> themes = {
        "Blue", "Green", "Aqua", "Red", "Purple", "Yellow", 
        "White", "Gray", "Light Blue"};
    int theme = 7;
    bool special_game_mode = false;
    int players = 2;
    int startCards = 7;
    void themes_screen(){
    system("cls");
        for(int i = 0; i<themes.size(); i++){
            cout<<i+1<<". "<<themes[i]<<endl;
        }
    string choice;
    try{
    getline(cin, choice);
    if (!isdigit(choice[0]) || choice[0] < '1' || choice[0] > '9') {
            throw Invalidinput();
        }
    this->theme = choice[0]-48;
    }
    catch(Invalidinput& mce){
        cout << mce.what();}
    }
    void players_screen(){
        try{
        system("cls");
        string choice;
        string startcards;
        cout << "Choose the amount of players (1-4): ";
        getline(cin, choice);
        if (!isdigit(choice[0]) || choice[0] < '1' || choice[0] > '4') {
            throw Invalidinput();
        }
        this->players = choice[0]-48;
        cin.clear();
        cout << "Choose the number of cards you want to start with: ";
        getline(cin, startcards);
        if (!isdigit(startcards[0]) || startcards[0] < '1' || startcards[0] > '9') {
            throw Invalidinput();
        }
        this->startCards= startcards[0]-48;
        }
        catch(Invalidinput& mce){
        cout << mce.what();
    }
    }
    void options_screen(){
         system("cls");
        try{
        string choice;
        cout<< "1. Themes"<<endl;
        cout<< "2. Set Players and starting cards"<<endl;
        cout<<"3. Enable/Disable Special Gamemode (only special cards are drawn)"<<endl<<endl;
        cout<<"Make a choice: "<<endl;
        getline(cin, choice);
         if (!isdigit(choice[0]) || choice[0] < '1' || choice[0] > '3') {
            throw Invalidinput();
        }
        if(choice[0] == '1')
        themes_screen();
        if(choice[0] == '2')
        players_screen();
        if(choice[0] == '3')
        special_game_mode = special_game_mode==true?false:true;
        }
        catch(Invalidinput& mce){
        cout << mce.what();}
    menu_screen();
    }
    void menu_screen(){
        system("cls");
        string choice;
        cout<< "1. Play"<<endl;
        cout<< "2. Options"<<endl<<endl;
        cout<<"Make a choice: "<<endl;
        try{
        getline(cin, choice);
        if (!isdigit(choice[0]) || choice[0] < '1' || choice[0] > '4') {
            throw Invalidinput();
        }
        if(choice[0] == '1')
        return;
        if(choice[0] == '2')
        options_screen();
        }
        catch(Invalidinput& mce){
        cout<<endl;
        cin.clear();
        cout << mce.what();}
    }

};
template<class T>
class CircularVector{

    public:
    int turn = 0;
    vector<T> a;

    T& at(int choice){
        return a[choice];
    }
    void next_turn(){
        if (turn+1 > a.size()-1){
            turn = 0;
        }
        else{
            turn++;
        }
    }
    // for the reverse-card
    void reverse(int choice){
    int current = choice;
    vector<T> temp;
    for (int i=0; i<a.size(); i++)  
        temp.push_back(a[i]);
    a.erase(a.begin(), a.end());
    //a.push_back(temp[choice]);
    //current--;
    int size = temp.size();
    for(int i = 0; i < size; i++){
        if(current == 0){
        a.push_back(temp[current]);
        temp.erase(temp.begin(), temp.begin()+choice);   // {0,1,2,3}
                                                            //{2,1,0,3}
        current = temp.size()-1;
        }
        else{
        a.push_back(temp[current]);
        current--;
        }
        }
        turn = 0; 

    }
    void push(T obj){
        a.push_back(obj);
    }
    int get_turn(){
        return turn;  
    }
    int size(){
        return a.size();
    }


};

class Card {
    public:
    virtual string about() {
        return " ";
    }
    virtual int get_number(){
        return -1;
    }
    virtual char get_color(){
        return 'n';
    }
    virtual void special(){
        return;
    }
};

// function prototype defined here, made in the end
void display_card_art(const vector<pair<Card*,string>*>&);


class NormalCard: public Card{
    public:
    int number;
    char color;

    NormalCard(int n, char c){
        number = n; color = c;
    }
    string about(){
        string a = color + to_string(number);
        return a;
    }
    int get_number(){
        return number;
    }
    char get_color(){
        return color;
    }

    
};

class Draw2Card : public Card{
    public:
    char color;

    Draw2Card(char c){
        color = c;
    }
    string about(){
        string a = "D2-" + string(1,color);
        return a;
    }
    char get_color(){
        return color;
    }
    
    void special(){
        Draw2Special();


    }
    int get_number(){
        return 201;
    }
    
};

class SkipCard : public Card{
    public:
    char color;

    SkipCard(char c){
        color = c;
    }
    string about(){
        string a = "S-" + string(1,color);
        return  a;
    }
    char get_color(){
        return color;
    }
    void special(){
        SkipSpecial();
    }
    int get_number(){
        return 202;
    }
};

class ReverseCard : public Card{
    public:
    char color;

    ReverseCard(char c){
        color = c;
    }
    string about(){
        string a = "Rev-" + string(1,color);
        return  a;
    }
    char get_color(){
        return color;
    }
    void special(){
        ReverseSpecial();
    }
    int get_number(){
        return 203;
    }
};

class Draw4Card : public Card{
    public:
    string about(){
        string a = "D-4";
        return a ;
    }

    void special(){
        Draw4Special();
    }
};

class WildCard : public Card{
    public:
    string about(){
        string a = "W-";
        return a ;
    }

    void special(){
        WildSpecial();

    }
};





class Deck {
public:
    //implementing maps using the pair object, both the pair and the card inside the pair are dynamically allocated
    vector<pair<Card*, string>*> cards = {};

    void initialize(bool special){
    if(special == false){
        cards.push_back(new pair<Card*, string>(new NormalCard(0, 'R'), "   _____   \n  |     |  \n  | R-0 |  \n  |_____|  \n"));
        cards.push_back(new pair<Card*, string>(new NormalCard(0, 'Y'), "   _____   \n  |     |  \n  | Y-0 |  \n  |_____|  \n"));
        cards.push_back(new pair<Card*, string>(new NormalCard(0, 'G'), "   _____   \n  |     |  \n  | G-0 |  \n  |_____|  \n"));
        cards.push_back(new pair<Card*, string>(new NormalCard(0, 'B'), "   _____   \n  |     |  \n  | B-0 |  \n  |_____|  \n"));
        
        for (int num = 1; num <= 9; ++num) {
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'R'), "   _____   \n  |     |  \n  | R-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'Y'), "   _____   \n  |     |  \n  | Y-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'G'), "   _____   \n  |     |  \n  | G-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'B'), "   _____   \n  |     |  \n  | B-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'R'), "   _____   \n  |     |  \n  | R-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'Y'), "   _____   \n  |     |  \n  | Y-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'G'), "   _____   \n  |     |  \n  | G-" + to_string(num) + " |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new NormalCard(num, 'B'), "   _____   \n  |     |  \n  | B-" + to_string(num) + " |  \n  |_____|  \n"));
        }
        
        for (int i = 0; i < 2; i++) {
            cards.push_back(new pair<Card*, string>(new Draw2Card('Y'), "   _____   \n  |     |  \n  | D2Y |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('G'), "   _____   \n  |     |  \n  | D2G |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('R'), "   _____   \n  |     |  \n  | D2R |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('B'), "   _____   \n  |     |  \n  | D2B |  \n  |_____|  \n"));
            
            cards.push_back(new pair<Card*, string>(new SkipCard('Y'), "   _____   \n  |     |  \n  | S-Y |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('G'), "   _____   \n  |     |  \n  | S-G |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('R'), "   _____   \n  |     |  \n  | S-R |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('B'), "   _____   \n  |     |  \n  | S-B |  \n  |_____|  \n"));
            
            cards.push_back(new pair<Card*, string>(new ReverseCard('Y'), "   _____   \n  |     |  \n  |Rev-Y|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('G'), "   _____   \n  |     |  \n  |Rev-G|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('R'), "   _____   \n  |     |  \n  |Rev-R|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('B'), "   _____   \n  |     |  \n  |Rev-B|  \n  |_____|  \n"));
        }
        
        for (int i = 0; i < 4; i++) {
            cards.push_back(new pair<Card*, string>(new Draw4Card(), "   _____   \n  |     |  \n  | D-4 |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new WildCard(), "   _____   \n  |     |  \n  |  W  |  \n  |_____|  \n"));
        }
    }
    else{
        for (int i = 0; i < 6; i++) {
            cards.push_back(new pair<Card*, string>(new Draw2Card('Y'), "   _____   \n  |     |  \n  | D2Y |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('G'), "   _____   \n  |     |  \n  | D2G |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('R'), "   _____   \n  |     |  \n  | D2R |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new Draw2Card('B'), "   _____   \n  |     |  \n  | D2B |  \n  |_____|  \n"));
            
            cards.push_back(new pair<Card*, string>(new SkipCard('Y'), "   _____   \n  |     |  \n  | S-Y |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('G'), "   _____   \n  |     |  \n  | S-G |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('R'), "   _____   \n  |     |  \n  | S-R |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new SkipCard('B'), "   _____   \n  |     |  \n  | S-B |  \n  |_____|  \n"));
            
            cards.push_back(new pair<Card*, string>(new ReverseCard('Y'), "   _____   \n  |     |  \n  |Rev-Y|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('G'), "   _____   \n  |     |  \n  |Rev-G|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('R'), "   _____   \n  |     |  \n  |Rev-R|  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new ReverseCard('B'), "   _____   \n  |     |  \n  |Rev-B|  \n  |_____|  \n"));
        }
        
        for (int i = 0; i < 18; i++) {
            cards.push_back(new pair<Card*, string>(new Draw4Card(), "   _____   \n  |     |  \n  | D-4 |  \n  |_____|  \n"));
            cards.push_back(new pair<Card*, string>(new WildCard(), "   _____   \n  |     |  \n  |  W  |  \n  |_____|  \n"));
        }
    }
    }



    pair<Card*, string>* drawCard() {
        int index = rand() % cards.size();
        pair<Card*, string>* drawnCard = cards[index];
        cards.erase(cards.begin() + index);
        return drawnCard;
    }

    void display_original() {
        for (int i = 0; i < cards.size(); i++)
        {
            cout << cards[i]->first->about()<<" ";
        }
        cout << endl;
    }
    void add_back(pair<Card*, string>* x) {
        cards.push_back(x);
    }

};

class Player {
public:
    int count = 0;
    int n = 0;
    Deck* sharedDeck;
    string name;
    char color = 'N';
    vector<pair<Card*,string>*>deck{};
    Player(const Player& other) : count(other.count), n(other.n), name(other.name), 
                                  sharedDeck(other.sharedDeck) {}
    Player(Deck* deck, string n) : sharedDeck(deck), name(n) {}


    void drawCards(int numCards) {
        for (int i = 0; i < numCards; ++i) {
            deck.push_back(sharedDeck->drawCard());
            count++;
        }
    }
    void display() {
        display_card_art(deck);
    }
};
Deck* sharedDeck = new Deck;
Player pool(sharedDeck, "pool"); 
CircularVector<Player*> players;
void turn(int choice){
    Player* currentplayer = players.at(choice);
while (true) {
            cout << currentplayer->name<< "'s turn" << endl;
            cout << endl;
            cout << "Your deck: "<<endl;
            currentplayer->display();
            cout << "Centre card: "<<endl;
            pool.display();
            int size = currentplayer->deck.size();
            cout << "Enter the card number you want to play (1 to " << size << ") or Enter (-1) to draw a card: " << endl;
            int ch;
            cin >> ch;

            if (cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong number! Please enter a valid number!" << endl;
                    cout << "---------------------------------------" << endl;
                    continue;
                }
        

            if ( ch == -1) {
                currentplayer->drawCards(1);
                size = currentplayer->deck.size();
                players.next_turn();
                break;
            }
            else  if ((ch - 1) >= 0 && (ch - 1) <= size) {
                pair<Card*, string>* card = currentplayer->deck[ch - 1];
                if ((pool.deck[0]->first->get_number() == card->first->get_number() && card->first->get_number() != -1)|| card->first->get_color() == pool.color
                  || card->first->about() == "D-4" || card->first->about() == "W-") {

                    currentplayer->sharedDeck->cards.push_back(pool.deck[0]); //push the pool card back into the shared deck
                    pool.deck.pop_back(); // remove the current pool card
                    pool.color = card->first->get_color();
                    card->first->special();
                    pool.deck.push_back(card); // replace the pool card with the users chosen card
                    currentplayer->deck.erase(currentplayer->deck.begin() + (ch - 1));
                    cout<<currentplayer->deck.size(); // remove the chosen card from the users deck
                    cout << "---------------------------------------" << endl;
                    players.next_turn();
                    break;
                }
                else {
                    cout << "Wrong number! Please enter a valid number!" << endl;
                    cout << "---------------------------------------" << endl;
                    continue;
                }

            }
            else {
                cout << "Wrong number! Please enter a valid number!" << endl;
                cout << "---------------------------------------" << endl;
                continue;
            }
        }
        

}
int main()
{
    
    srand(static_cast<unsigned int>(time(0)));

    Menu game_menu;
    game_menu.menu_screen();
    system("cls");
    sharedDeck->initialize(game_menu.special_game_mode);
    for(int i = 1; i <= game_menu.players; i++){
        cout<<"Enter the name of player "<< i<<endl;
        string name;
        getline(cin, name);
        Player* a = new Player(sharedDeck, name);
        a->drawCards(game_menu.startCards);
        players.push(a);
    }

   // setting colors
    HANDLE console_color; 
    console_color = GetStdHandle( 
        STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute( 
            console_color, game_menu.theme); 
    while (true){

    // setting players
     pool.drawCards(1);// Card to start the game
    auto card = pool.deck[0];
    if(card->first->about() == "D-4" || card->first->about() == "W-"){
         pool.sharedDeck->cards.push_back(pool.deck[0]); //push the pool card back into the shared deck
                    pool.deck.pop_back();
    }
    else{
        break;
    }
    }
    pool.color= pool.deck[0]->first->get_color();
    //sharedDeck.display_original();
    while (true) {
        system("cls");
        int player = players.get_turn();
        turn(player);
        auto currentplayer = players.at(player);
         if (currentplayer->deck.size() == 0) {
                     cout << currentplayer->name << " has won!";
                    cout << endl<<endl;
                    for(auto card : sharedDeck->cards){
                        delete card->first;
                        delete card;
                    }
                    for(auto player : players.a){
                        delete player;
                    }

                    return 0;
        }


    }

}
void SkipSpecial(){
    players.next_turn();
}

void ReverseSpecial(){
    if (players.size() == 2)
        players.next_turn();
    else
     players.reverse(players.get_turn());
}

void Draw4Special(){
    Player* player = nullptr;
    if(players.get_turn() == players.size()-1  )
        player =  players.at(0);
    else
        player =  players.at(players.get_turn() + 1);
    player->drawCards(4);
    char col;
    string input;
    
    cout << "Choose a color (R,G,B,Y): "<<endl;
    while (true) {
        cin.sync();
        getline(cin, input);
        if (input.length() != 1) {
            cout << "Invalid color, Choose a color (R,G,B,Y): "<<endl;
            continue;
        }
        
        col = input[0];
        if (col != 'R' && col != 'G' && col != 'B' && col != 'Y') {
            cout << "Invalid color, Choose a color (R,G,B,Y): "<<endl;
            continue;
        } else {
            pool.color = col;
            break;
        }
    }
}

void WildSpecial(){
    char col;
    string input;
    
    cout << "Choose a color (R,G,B,Y): "<<endl;
    while (true) {
        cin.sync();
        getline(cin, input);
        if (input.length() != 1) {
            cout << "Invalid color, Choose a color (R,G,B,Y): "<<endl;
            continue;
        }
        
        col = input[0];
        if (col != 'R' && col != 'G' && col != 'B' && col != 'Y') {
            cout << "Invalid color, Choose a color (R,G,B,Y): "<<endl;
            continue;
        } else {
             pool.color = col;
            break;
        }
    }
        
}

void Draw2Special(){
    Player* player = nullptr;
    
    if(players.get_turn() == players.size()-1  )
        player =  players.at(0);
    else
        player =  players.at(players.get_turn() + 1);
    player->drawCards(2);
    cout<<player->name;
}

void display_card_art(const vector<pair<Card*,string>*>& cards){
    vector<string> card_art;
    for (const auto cardPair : cards) {
            card_art.push_back(cardPair->second);
            
        }
    vector<string> combinedLines;   
   // Split each card into lines
    vector<vector<string>> lines;
    for (const auto& c : card_art) {
        vector<string> cardLines;
        size_t startPos = 0;
        size_t endPos = c.find('\n');
        while (endPos != string::npos) {
            cardLines.push_back(c.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = c.find('\n', startPos);
        }
        cardLines.push_back(c.substr(startPos)); // Last line
        lines.push_back(cardLines);
    }

    // Combine lines from each card
    for (size_t i = 0; i < lines[0].size(); ++i) {
        string combinedLine;
        for (const auto& cardLines : lines) {
            combinedLine += cardLines[i] + " ";
        }
        combinedLines.push_back(combinedLine);
    }

    for (const auto& line : combinedLines) {
        cout << line << endl;
    }
}