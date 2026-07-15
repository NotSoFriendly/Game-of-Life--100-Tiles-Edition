#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ==================== CONSTANTS ====================
#define TOTAL_TILES 100

// TILE TYPES:
// S = Start F = Finish
// C = Career P = Payday
// H = House D = Decision
// G = Gamble $ = Event
// . = Normal X = You (on map)

// ==================== CLEAR SCREEN & ANSI ====================
void cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void enableAnsi() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    GetConsoleMode(h, &m);
    SetConsoleMode(h, m | 0x0004);
#endif
}

// ==================== TILE CLASS ====================
class Tile {
public:
    char type;
    string label;
    Tile() : type('.'), label("NORMAL") {}
    Tile(char t, string l) : type(t), label(l) {}
};

// ==================== PLAYER CLASS ====================
class Player {
public:
    int money;
    int position;
    string career;
    int salary;
    string house;
    int houseprice;

    Player() : money(15000), position(0), career("None"),
               salary(0) {}

    void showStatus(string tileName) {
        cout << "\n====================================\n";
        cout << " INVENTORY / STATUS\n";
        cout << "====================================\n";
        cout << " Money : $" << money << "\n";
        cout << " Tile : " << position << " / 99 (" << tileName << ")\n";
        cout << " Career : " << career << "\n";
        cout << " Salary : $" << salary << " per payday" << "\n";
        cout << " House : " << house << "\n";
        cout << " House cost : " << houseprice << "\n";
        cout << "====================================\n";
    }
};

// ==================== GAME MAP CLASS ====================
class GameMap {
public:
    Tile tiles[TOTAL_TILES];

    GameMap() {
        for (int i = 0; i < TOTAL_TILES; i++)
            tiles[i] = Tile('.', "NORMAL");

        tiles[0] = Tile('S', "START");
        tiles[99] = Tile('F', "FINISH");

        // 1 Career, 1 House
        tiles[20] = Tile('C', "CAREER");
        tiles[55] = Tile('H', "HOUSE");

        // Payday tiles (automatic salary collection)
        int pArr[] = {10,25, 36, 43, 51, 61, 71, 81, 90, 98};
        for (int x : pArr) tiles[x] = Tile('P', "PAYDAY");

        // Event tiles
        int eArr[] = {8, 18, 35, 50, 70, 78, 88, 95, 33, 37, 42, 46, 52, 57, 63, 66, 72, 84, 93, 97, 2,
             4, 6, 7, 9, 11, 13, 16, 22, 24, 27, 29};
        for (int x : eArr) tiles[x] = Tile('$', "EVENT");

        // 5 Gamble tiles spread across the path
        int gArr[] = {15, 38, 60, 75, 92, 31, 44, 64, 73, 86};
        for (int x : gArr) tiles[x] = Tile('G', "GAMBLE");
    }

    Tile getTile(int pos) { return tiles[pos]; }

    void draw(int playerPos) {
        string border = "+----------------------------------------+";
        cout << "\n";
        cout << " GAME OF LIFE - 100 TILE MAP\n";
        cout << " " << border << "\n";
        for (int row = 0; row < 10; row++) {
            int start, end, step;
            if (row % 2 == 0) { start = row*10; end = row*10+9; step = 1; }
            else { start = row*10+9; end = row*10; step = -1; }

            cout << " |";
            for (int t = start; step > 0 ? t <= end : t >= end; t += step) {
                if (t == playerPos) cout << " X |";
                else cout << " " << tiles[t].type << " |";
            }
            cout << "\n";
        }
        cout << " " << border << "\n";
        cout << "\n";
    }

    void redraw(int playerPos) {
        cls();
        draw(playerPos);
    }
};

// ==================== CAREER CLASS ====================
class CareerBlock {
private:
    string careers[6] = {
        "Engineer", "Doctor", "Artist",
        "Business Owner", "Teacher", "Game Developer"
    };
    int salaries[6] = {3000, 5000, 2000, 6000, 2500, 4000};
            
        //Different display for different career
        void display(int dic){
        if (dic==1){
        cout<<"Congratulations, you are now a Software Engineer\n";
        cout<<"You have officially joined one of the most exciting and in-demand careers in the world!\n";
        cout<<"You will be earning a solid $3,000 salary\n";
        cout<<"While building apps, systems, and products that millions of people use every single day.\n";
        cout<<"The growth, opportunities, and financial freedom ahead of you are truly limitless"<<endl;
        }
        if (dic==2){
        cout<<"Congratulations, you are now a Doctor\n";
        cout<<"You have officially stepped into one of the most respected and noble professions in the entire world!\n";
        cout<<"You will be earning a well-deserved $5,000 salary\n";
        cout<<"While saving lives and making a real difference in people's health every single day.\n";
        cout<<"The fulfillment, the impact, and the incredible journey ahead of you are truly beyond words"<<endl;
        }
        if (dic==3){
        cout<<"Congratulations, you are now a professional Artist\n";
        cout<<"You have officially turned your passion and creativity into a real career, which most people only ever dream of!\n";
        cout<<"You will be earning $2,000 doing what you truly love\n";
        cout<<"Creating art that inspires, moves, and leaves a lasting impression on everyone who sees it.\n";
        cout<<"The freedom, the creativity, and the beautiful journey ahead of you are truly one of a kind"<<endl;
        }
        if (dic==4){
        cout<<"Congratulations, you are now a Business Owner\n";
        cout<<"You have officially taken the bold step of building something of your very own, which takes real courage and vision!\n";
        cout<<"You will be earning $6,000 while running your own show, making your own decisions\n";
        cout<<"Creating opportunities not just for yourself but for everyone around you.\n";
        cout<<"The success, the independence, and the amazing journey of growing your own business ahead of you are truly limitless"<<endl;
        }
        if (dic==5){
        cout<<"Congratulations, you are now a Teacher\n";
        cout<<"You have officially joined one of the most important and impactful professions in the entire world\n";
        cout<<"Because everything starts with a great teacher! You will be earning $2,500\n";
        cout<<"While shaping young minds, inspiring the next generation, and leaving a legacy that will last far beyond your classroom.\n";
        cout<<"The respect, the purpose, and the incredible reward of knowing you changed someone's life ahead of you are truly priceless "<<endl;
        }
        if (dic==6){
        cout<<"Congratulations, you are now a Game Developer\n";
        cout<<"You have officially joined one of the most creative and fast-growing industries in the entire world\n";
        cout<<"Where imagination and technology come together! You will be earning $4,000\n";
        cout<<"While designing, building, and bringing to life the games that millions of players around the world will enjoy and love.\n";
        cout<<"The creativity and the thrilling journey of turning your ideas into gaming experiences ahead of you are truly extraordinary "<<endl;
        }
        }


public:
    void trigger(Player& player, GameMap& gmap) {
        gmap.redraw(player.position);

        cout << "------------------------------------\n";
        cout << " CAREER TILE!\n";
        cout << "------------------------------------\n";
        cout << " Roll the dice to get your career!\n\n";
        cout << " Dice Career Salary\n";
        cout << " ---------------------------------\n";
        for (int i = 0; i < 6; i++) {
            cout << " [" << i+1 << "] ";
            string name = careers[i];
            while ((int)name.length() < 20) name += " ";
            cout << name << "$" << salaries[i] << "\n";
        }
        cout << "\n Press Enter to roll the dice...";
        cin.get();

        int dice = rand() % 6 + 1;
        player.career = careers[dice - 1];
        player.salary = salaries[dice - 1];
        gmap.redraw(player.position);
        cout << "------------------------------------\n";
        cout << " Dice rolled : " << dice << "\n";
        cout << " Career assigned: " << player.career << "\n";
        cout << " Salary : $" << player.salary << " per payday\n";
        display(dice);
        cout << "------------------------------------\n";
        cout << "\n Press Enter to continue...";
        cin.get();
    }
};

// =================== PAYDAY CLASS ====================
class PaydayBlock {
public:
    // Returns true if payday was triggered (for message display)
    bool trigger(Player& player) {
        if (player.salary > 0) {
            player.money += player.salary;
            return true;
        }
        return false;
    }
};

// ==================== HOUSE CLASS ====================
class HouseBlock {
private:
    struct House { string name; int price; };
    House houses[6] = {
        {"Studio Apartment", 25000},
        {"1BHK Flat", 45000},
        {"2BHK Apartment", 70000},
        {"3BHK Apartment", 95000},
        {"Suburban Villa", 150000},
        {"Luxury Penthouse", 250000}
    };

    
    //Different display for different houses
    void display(int cho){
    if (cho==1){
    cout<<" Congratulations on your incredible milestone owning your very own studio apartment is a dream that many aspire to\n";
    cout<<"You've made it a reality! This $25,000 investment is not just a property, but a place you can truly call your own home.\n";
    cout<<"Wishing you endless joy, comfort, and wonderful memories in your brand-new space!"<<endl;
    }
    if (cho==2){
    cout<<"Congratulations on the amazing achievement of purchasing your very own 1 BHK flat\n";
    cout<<"A smart and significant investment of $45,000 that marks a truly proud moment in your life!\n";
    cout<<"Your new home is a perfect blend of comfort and space, offering you the freedom to create beautiful memories in every corner.\n";
    cout<<"Wishing you a lifetime of happiness, prosperity, and wonderful new beginnings in your lovely new home!"<<endl;
    }
    if (cho==3){
    cout<<" Congratulations on the spectacular achievement of becoming the proud owner of a 2 BHK flat\n";
    cout<<"A wonderful investment of $70,000 that truly reflects your hard work, dedication, and smart financial planning!\n";
    cout<<"This spacious home is perfect for you and your loved ones, offering the privacy and room to grow that every family deserves.\n";
    cout<<"Wishing you a lifetime filled with joy, laughter, love, and countless beautiful memories in your gorgeous new home! "<<endl;
    }
    if (cho==4){
    cout<<" Congratulations on the truly remarkable achievement of owning a magnificent 3 BHK apartment\n";
    cout<<"An outstanding investment of $95,000 that stands as a shining testament to your relentless hard workk and brilliant financial vision!\n";
    cout<<"This spacious and elegant home is a perfect sanctuary for you and your entire family\n";
    cout<<"Offering abundant room, comfort, and warmth to nurture beautiful relationships and create lifelong cherished memories together.\n";
    cout<<"Wishing you endless happiness, prosperity, good health, and a lifetime of love and laughter\n";
    cout<<"As you step into this wonderful new chapter of your life in your dream home! "<<endl;
    }
    if (cho==5){
    cout<<" Congratulations on becoming the proud owner of a stunning suburban villa worth $150,000\n";
    cout<<"A remarkable milestone that reflects your dedication and financial wisdom!\n";
    cout<<"This beautiful retreat is the perfect place for you and your family to create lifelong memories, enjoy peaceful living\n";
    cout<<"And embrace a lifestyle you truly deserve. Wishing you endless happiness and prosperity in your dream home! "<<endl;
    }
    if (cho==6){
    cout<<" Congratulations on becoming the proud owner of a magnificent luxury penthouse worth $250,000\n";
    cout<<"An extraordinary achievement that truly reflects your ambition, success, and impeccable taste!\n";
    cout<<"Perched at the top of the world, this stunning penthouse is the ultimate symbol of elegance and sophistication\n";
    cout<<"Offering you breathtaking views and a lifestyle that is second to none.\n";
    cout<<"Wishing you a lifetime of luxury, happiness, and unforgettable memories in your dream penthouse!"<<endl;
    }
    }

public:
    void trigger(Player& player, GameMap& gmap) {
        gmap.redraw(player.position);

        cout << "------------------------------------\n";
        cout << " HOUSE TILE!\n";
        cout << "------------------------------------\n";
        cout << " Your Money: $" << player.money << "\n\n";

        bool canAffordAny = false;
        for (int i = 0; i < 6; i++) {
            if (player.money >= houses[i].price) { canAffordAny = true; break; }
        }

        cout << " # House Price Status\n";
        cout << " ---------------------------------------------------\n";
        for (int i = 0; i < 6; i++) {
            cout << " [" << i+1 << "] ";
            string name = houses[i].name;
            while ((int)name.length() < 20) name += " ";
            cout << name << " $" << houses[i].price;
            if (player.money >= houses[i].price) cout << " [CAN BUY]";
            else cout << " [too expensive]";
            cout << "\n";
        }

        if (!canAffordAny) {
            cout << "\n------------------------------------\n";
            cout << " You couldn't save enough for\n";
            cout << " a house. GAME OVER!\n";
            cout << "------------------------------------\n";
            exit(0);
        }

        int choice = 0;
        while (true) {
            cout << "\n Choose a house (1-6): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice < 1 || choice > 6) {
                cout << " Invalid choice. Try again.\n"; continue;
            }
            if (player.money < houses[choice-1].price) {
                cout << " You cannot afford that! Choose another.\n"; continue;
            }
            break;
        }

        player.money -= houses[choice-1].price;
        player.house =  houses[choice-1].name;
        player.houseprice = houses[choice-1].price;

        gmap.redraw(player.position);
        cout << "------------------------------------\n";
        cout << " You bought: " << houses[choice-1].name << "!\n";
        cout << " Money left: $" << player.money << "\n";
        display(choice);
        cout << "------------------------------------\n";
        cout << "\n Press Enter to continue...";
        cin.get();
    }
};

// ==================== EVENT CLASS ====================
class EventBlock {
private:
    string payEvents[30] = {
        "Your car had an accident!",
        "Medical emergency! Hospital bill.",
        "Your phone got stolen.",
        "Roof leak at home. Repair needed.",
        "You got a traffic fine.",
        "A bad business deal went wrong.",
        "Flood damaged your property.",
        "Your laptop crashed. Need a new one.",
        "Your bike broke down on the highway.",
        "Your wallet got lost in the market.",
        "Unexpected dental treatment needed.",
        "Your house power wiring short-circuited.",
        "Your pet needs urgent surgery.",
        "Your car tire burst and damaged the rim.",
        "Your air conditioner suddenly stopped working.",
        "A water pipe burst in your bathroom.",
        "You lost money in an online scam.",
        "Your fridge compressor failed.",
        "Your window glass shattered in a storm.",
        "Your luggage got lost during travel.",
        "Unexpected legal fees for a dispute.",
        "Your washing machine motor burned out.",
        "Your phone screen cracked badly.",
        "Your shop inventory got damaged.",
        "A tree fell and damaged your fence.",
        "Your internet router burned out.",
        "You misplaced an important document.",
        "Your scooter battery died suddenly.",
        "Your laptop got stolen from It park.",
        "Your parking ticket penalty increased."
    };
    int payCost[30] = {5000, 8000, 3000, 4000, 1500, 6000, 7000, 2500,  3200, 1500, 4500, 5200, 7800, 3900, 6500, 2700, 9000, 
        7200, 1800, 4100, 8500, 5600, 2200, 6900, 3100, 1400, 800, 1600, 9300, 1200};

    string winEvents[30] = {
        "You won the lottery!",
        "Stock market paid off!",
        "You found a wallet. Honest reward.",
        "Your YouTube channel went viral!",
        "Tax refund arrived.",
        "You sold old stuff online.",
        "Bonus from your company!",
        "Scratch card win!",
        "Your old investment matured.",
        "You won a small online giveaway.",
        "You got cashback from a payment app.",
        "Your landlord returned the security deposit.",
        "You earned money from selling photos online.",
        "You got a performance reward at work.",
        "You received unexpected royalty income.",
        "You found money in an old jacket pocket.",
        "Your side hustle made a profit.",
        "You received a scholarship reward.",
        "You got referral bonus from a friend.",
        "You sold your old bike parts.",
        "Your blog post earned ad revenue.",
        "You won a local competition prize.",
        "You got refund from a cancelled order.",
        "A friend returned money you lent earlier.",
        "You earned interest from your savings.",
        "You received a gift card reward.",
        "You received a surprise inheritance.",
        "Your startup idea got funded!",
        "You found treasure in a cave.",
        "You won a small gaming tournament prize!"
    };
    int winAmount[30] = {20000, 12000, 3000, 8000, 5000, 2000, 10000, 15000,  4500, 6200, 12000, 3500, 2100, 8000, 7000, 9200, 
        17500, 1500, 11000, 20000, 5200, 4300, 6500, 16000, 3200, 5500, 2200, 24000, 100000, 13000};

public:
    void trigger(Player& player, GameMap& gmap) {
        gmap.redraw(player.position);
        int coin = rand() % 2;
        cout << "------------------------------------\n";
        cout << " EVENT TILE!\n";
        cout << "------------------------------------\n";
        if (coin == 0) {
            int idx = rand() % 30;
            cout << " BAD LUCK! " << payEvents[idx] << "\n";
            cout << " You pay : -$" << payCost[idx] << "\n";
            player.money -= payCost[idx];
        } else {
            int idx = rand() % 30;
            cout << " GOOD LUCK! " << winEvents[idx] << "\n";
            cout << " You earn : +$" << winAmount[idx] << "\n";
            player.money += winAmount[idx];
        }
        cout << " Money now : $" << player.money << "\n";
        cout << "------------------------------------\n";
        cout << "\n Press Enter to continue...";
        cin.get();
    }
};

// ==================== GAMBLE CLASS ====================
class GambleTile {
public:
    void trigger(Player& player, GameMap& gmap, int tileNum) {
        gmap.redraw(player.position);

        char choice;
        cout << "------------------------------------\n";
        cout << " GAMBLE TILE [" << tileNum << "]\n";
        cout << "------------------------------------\n";
        cout << " Your Money : $" << player.money << "\n\n";
        cout << " Guess the dice & win 4x your bet!\n";
        cout << " Wrong guess = lose your bet.\n\n";
        cout << " Do you want to gamble? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice != 'Y' && choice != 'y') {
            cout << "\n You passed. Moving on!\n";
            cout << "\n Press Enter to continue...";
            cin.get();
            return;
        }

        int bet;
        cout << "\n Enter bet: $";
        cin >> bet;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (bet <= 0 || bet > player.money) {
            cout << "\n Invalid bet. Skipping gamble.\n";
            cout << "\n Press Enter to continue...";
            cin.get();
            return;
        }

        int guess;
        cout << " Pick a number (1-6): ";
        cin >> guess;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (guess < 1 || guess > 6) {
            cout << "\n Invalid number. Skipping gamble.\n";
            cout << "\n Press Enter to continue...";
            cin.get();
            return;
        }

        int dice = rand() % 6 + 1;
        cout << "\n Dice rolled : " << dice << "\n";
        if (dice == guess) {
            cout << " YOU WON! +$" << bet * 4 << "\n";
            player.money += bet * 4;
        } else {
            cout << " You lost! -$" << bet << "\n";
            player.money -= bet;
        }
        cout << " Money now : $" << player.money << "\n";
        cout << "------------------------------------\n";
        cout << "\n Press Enter to continue...";
        cin.get();
    }
};

// ==================== GAME CLASS ====================
class Game {
private:
    Player player;
    GameMap gmap;
    CareerBlock career;
    PaydayBlock payday;
    HouseBlock house;
    EventBlock event;
    GambleTile gamble;

    void showIntro() {
        cls();
        cout << "\n";
        cout << "**********************************************************************************************************************\n";
        cout << "* GAME OF LIFE *\n";
        cout << "* 100 Tile Edition *\n";
        cout << "Welcome to a journey where every roll of the dice feels like destiny calling your name!\n";
        cout<<"Ahead lies a road filled with triumph, risk, and moments that will test your courage!\n";
        cout<<"The path is uncertain, the stakes are real, and fortune waits silently around every corner!\n";
        cout<<"Some steps will reward you, others will challenge you! Every move writes a new chapter of your story!\n";
        cout<<"Take a deep breath, steady your mind, and step forward with confidence... because your adventure begins right now!\n";
        cout << "**********************************************************************************************************************\n\n";

        cout << "STORY:\n";
        cout << " Navigate 100 tiles of life! Get a career,\n";
        cout << " collect salary at paydays, buy a house,\n";
        cout << " survive random events, and reach FINISH!\n\n";

        cout << "TILE GUIDE:\n";
        cout << " X = You - Your current position on the map\n";
        cout << " S = Start - Where your journey begins\n";
        cout << " F = Finish - Reach here to WIN\n";
        cout << " C = Career - Roll dice, get assigned a career\n";
        cout << " P = Payday - Salary auto-collected as you pass\n";
        cout << " H = House - You must buy a house here\n";
        cout << " G = Gamble - Choose to bet or skip\n";
        cout << " $ = Event - Random unfortunate incident (pay) or Random fortunate event (win)\n";
        cout << " . = Normal - Nothing happens\n\n";

        cout << "NOTES:\n";
        cout << " - Special tiles (C, H) are forced stops\n";
        cout << " - Special tiles ($, G) are non forced stops\n";
        cout << " - Payday (P) is automatic as you pass through it\n";
        cout << " - If you can't afford any house, the game ends\n\n";

        cout << "CONTROLS:\n";
        cout << " Press Enter -> Roll dice and move\n";
        cout << " Press M -> View your status and inventory\n\n";

        cout << "STARTING MONEY: $15,000\n\n";
        cout << " Press Enter to begin...";
        cin.get();
        cls(); // clear intro before map draws
    }

    void showWin() {
        gmap.redraw(player.position);
        cout << "**********************************************\n";
        cout << "* YOU WIN!!! *\n";
        cout << "**********************************************\n\n";
        cout << " Congratulations! You finished the Game of Life!\n\n";
        cout << " Final Money : $" << player.money << "\n";
        cout << " Career : " << player.career << "\n";
        cout << " Houses Owned : " << player.house << "\n";
        cout << " Houses Price : " << player.houseprice << "\n\n";
        if (player.money + player.houseprice >= 200000) {
        cout << " Rating: TYCOON! You are legendary!\n";
        cout << " You conquered every twist of fate and rose above every challenge life placed before you!\n";
        cout << " Wealth, courage, and relentless determination carried you to the very top. Few reach this level of greatness.\n"; 
        cout << " Your journey ends not just in victory, but in legend. The world now recognizes you as a true master of success.\n";
        }
        else if ((player.money + player.houseprice) >= 100000){
        cout << " Rating: MILLIONAIRE! Outstanding!\n";
        cout << " Your journey through life has rewarded you with remarkable success!\n";
        cout << " Through smart choices, resilience, and a bit of fortune, you built a life of impressive wealth and stability.\n";
        cout << " Not everyone reaches this level, but you did. Stand proud, because today you finish this adventure as a true Millionaire!\n";
        }
        else if ((player.money + player.houseprice) >= 75000) {
        cout << " Rating: WEALTHY! Great job!\n";
        cout << " You managed life's twists with wisdom and steady determination!\n";
        cout << " Step by step, you built comfort, security, and a future many dream of achieving.\n";
        cout << " Challenges came and went, but you stayed strong and kept moving forward.\n";
        cout << "Today you stand successful and respected, finishing this journey as someone truly Wealthy!\n";
        }
        else if ((player.money + player.houseprice) >= 60000) {
        cout << " Rating: STABLE! Not bad at all!\n";
        cout << " You navigated life with patience and balance!\n";
        cout << " Not every road was easy, but you stayed steady through the ups and downs.\n";
        cout << " Your choices built a life of stability and security. It may not be the grandest fortune, but it is honest success.\n";
        cout << " You finish this journey proud, resilient, and Stable!\n";
        }
        else if ((player.money + player.houseprice) >= 30000) {
        cout << " Rating: SURVIVED! Just barely!\n";
        cout << " The journey was tough, unpredictable, and full of challenges, but you never gave up!\n";
        cout << " When life pushed hard, you pushed back harder. Every step forward was earned with grit and determination.\n";
        cout << " You may not leave with great riches, but you leave with something just as powerful — you survived!\n";
        }
        else {
        cout << " Rating: BROKE! Life was rough!\n";
        cout << " The road was harsh, the odds were unforgiving, and fortune rarely stood by your side!\n";
        cout << " Every step felt heavier than the last, and the journey drained everything you had. Yet you reached the end.\n";
        cout << " No riches remain, no fortune to celebrate… but your story still stands. This time, life left you broke.\n";
        }
        cout << "\n Thanks for playing!\n";
        cout << "**********************************************\n";
    }

    void showGameOver() {
        gmap.redraw(player.position);
        cout << "**********************************************\n";
        cout << "* GAME OVER! *\n";
        cout << "**********************************************\n\n";
        cout << " You ran out of money on tile " << player.position << ".\n";
        cout << " Career : " << player.career << "\n\n";
        cout << " Better luck next time!\n";
        cout << "**********************************************\n";
    }

    // Move step by step, stop at any special tile
    // Returns true if a special tile was hit
    bool movePlayer(int dice) {
        for (int step = 0; step < dice; step++) {
            player.position++;

            if (player.position >= TOTAL_TILES) {
                player.position = TOTAL_TILES - 1;
                return false;
            }

            char t = gmap.getTile(player.position).type;

            // Payday is automatic — collect and keep moving
            if (t == 'P') {
                bool got = payday.trigger(player);
                gmap.redraw(player.position);
                cout << "------------------------------------\n";
                if (got)
                    cout << " PAYDAY! Salary +$" << player.salary
                         << " collected automatically!\n";
                else
                    cout << " PAYDAY tile - no career yet, no salary.\n";
                cout << " Money now : $" << player.money << "\n";
                cout << "------------------------------------\n";
                cout << "\n Press Enter to continue moving...";
                cin.get();
                continue;
            }

            //  special tiles = career and house-force stop
            if (t == 'C' || t == 'H' ||
                t == 'F') {
                return true;
            }
        }
        // gamble and envent tile also special-no force stop
        char t = gmap.getTile(player.position).type;
        if (t == '$') event.trigger(player, gmap);
        if (t == 'G') gamble.trigger(player, gmap, player.position); 
        return false;

    }

    void handleTile() {
        char t = gmap.getTile(player.position).type;
        if (t == 'C') career.trigger(player, gmap);
        else if (t == 'H') house.trigger(player, gmap);
    }

public:
    void run() {
        srand(time(0));
        enableAnsi();
        showIntro();
        // Intro already called cls() — now draw map once
        gmap.draw(player.position);

        while (true) {

            if (player.position >= TOTAL_TILES - 1) {
                showWin();
                return;
            }

            cout << " Press Enter to roll (M = status): ";
            string input;
            getline(cin, input);

            // Status / inventory
            if (input == "m" || input == "M") {
                player.showStatus(gmap.getTile(player.position).label);
                cout << "\n Press Enter to continue...";
                cin.get();
                gmap.redraw(player.position);
                continue;
            }

            // Roll dice
            int dice = rand() % 6 + 1;
            gmap.redraw(player.position);
            cout << " You rolled: " << dice << "! Moving...\n";
            cout << " Press Enter to move...";
            cin.get();

            bool stoppedAtSpecial = movePlayer(dice);

            // Redraw map with updated position
            gmap.redraw(player.position);

            // Handle special tile if stopped
            if (stoppedAtSpecial) {
                handleTile();
            }

            if (player.money <= 0) {
                showGameOver();
                return;
            }

            // Redraw map cleanly after event text
            gmap.redraw(player.position);
        }
    }
};

// ==================== MAIN ====================
int main() {
    Game g;
    g.run();
    return 0;
}