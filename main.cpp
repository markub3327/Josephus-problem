    //  8. Napíšte funkcie a otestujte, ktoré pre cyklicky zreťazený zoznam (Jozefov problém) 
    //      a) pre zadaný ukazovateľ na bojovníka nájdu momentálny počet bojovníkov v zozname a vypíšu ich  // ok
    //      b) pre dva ukazovatele na rôznych dvoch bojovníkov nájdu počet bojovníkov medzi nimi    // ok
    //      c) pre daný ukazovateľ vloží za bojovníka momentálne zadaných ďalších bojovníkov

    #include <iostream>

    class Bojovnik  // vrchol v zozname predstavuje bojovnika
    {
        private:
            Bojovnik *dalsi;    // odkaz na nasledujuceho bojovnika v zozname
            uint64_t id;        // jedinecny identifikator bojovnika urceny poradim v zozname
        public:
            Bojovnik(uint64_t id, Bojovnik *dalsi) : id(id), dalsi(dalsi) {}

            // Getter
            uint64_t getId() { return this->id; }
            Bojovnik *getDalsi() { return this->dalsi; }

            // Setter
            void setDalsi(Bojovnik *dalsi) { this->dalsi = dalsi; }
    };

    class ZoznamBojovnikov  // Trieda zoznamu
    {
        private:
            Bojovnik *hlava;     // odkaz na prveho bojovnika v zozname
            Bojovnik *chvost;    // odkaz na posledneho bojovnika
        public:
            ZoznamBojovnikov(uint64_t pocet_bojovnikov)  // konstruktor zoznamu pre dany pocet bojovnikov
            {
                if (pocet_bojovnikov > 0)
                {
                    this->chvost = this->hlava = new Bojovnik(1, this->hlava);   // pridaj prveho bojovnika
                    for (Bojovnik *vyber = this->hlava; vyber->getId() != pocet_bojovnikov; vyber = vyber->getDalsi()) // dokym nebude id bojovnika zhodne s poctom bojovnikov
                    {
                        this->chvost = new Bojovnik((vyber->getId()+1), this->hlava);   // vytvor noveho bojovnika na konci zoznamu
                        vyber->setDalsi(this->chvost);  // pridaj bojovnika za predposledneho
                    }
                }
                else
                {
                    this->hlava = this->chvost = NULL;  // prazdny zoznam bojovnikov
                }
            }

            Bojovnik *vybiBojovnikov(int kazdyKolky)    // funkcia vrati posledneho bojovnika po vybijani
            {
                Bojovnik *vyber;

                if (kazdyKolky > 0)
                {
                    for (vyber = this->chvost; vyber != vyber->getDalsi();)
                    {
                        for (int i = 1; i < kazdyKolky; i++) 
                        {
                            vyber = vyber->getDalsi();
                        }

                        auto tmp = vyber->getDalsi();   // odkaz na vyluceneho bojovnika
                        std::cout << "Vybil sa " << tmp->getId() << ". bojovnik" << std::endl;
                        vyber->setDalsi(tmp->getDalsi());   // posun ukazatel o jednoho bojovnika dalej (vynechanim bojovnika vylucime)
                        delete tmp;  // vycisti pametove miesto po vylucenom bojovnikovi
                    }

                    this->hlava = this->chvost = vyber; // zostal iba 1 posledny bojovnik po vybiti

                    return vyber;
                }
                else
                {
                    return NULL;
                }
            }

            uint64_t pocetBojovnikov(Bojovnik *bojovnik)
            {
                uint64_t pocitadlo = 1;

                if (bojovnik)
                {
                    std::cout << "Bojovnik " << bojovnik->getId() << std::endl; 

                    for (Bojovnik *vyber = bojovnik->getDalsi(); vyber != bojovnik; vyber = vyber->getDalsi())  // prejdi zoznam od zadaneho bojovnika po zadaneho bojovnika (dokolecka)
                    {
                        std::cout << "Bojovnik " << vyber->getId() << std::endl; 
                        pocitadlo ++;   // pocitadlo bojovnikov navys o jedneho
                    }
                }
                else
                {
                    return 0;
                }
                
                return pocitadlo;
            }

            uint64_t vzdialenostBojovnikov(Bojovnik *A, Bojovnik *B)
            {
                uint64_t pocitadlo = 0;

                if (A && B)
                {
                    for (Bojovnik *vyber = A; vyber != B; vyber = vyber->getDalsi()) // prejdi zoznam bojovnikov v zvolenom rozsahu pointrami
                    {
                        pocitadlo ++;   // pocitadlo prechodov navys o jedna
                    }
                }
                else
                {
                    return 0;
                }
                
                return pocitadlo;
            }

            void pridajBojovnikov(Bojovnik *bojovnik, uint64_t pocet_bojovnikov)
            {
                auto tmp = bojovnik->getDalsi();
            }

            Bojovnik *getHlava() { return this->hlava; }
            Bojovnik *getChvost() { return this->chvost; }
    };

    int main()
    {
        ZoznamBojovnikov *armada;

        // hlavicka
        std::cout << "Martin Horvath, Copyright 2019" << std::endl;
        std::cout << "1. rocnik, Aplikovana informatika" << std::endl;
        std::cout << "Jozefov problem" << std::endl << std::endl;

        // vytvor armadu
        int N;
        std::cout << "Zadajte pocet bojovnikov: ";
        std::cin >> N;
        armada = new ZoznamBojovnikov(N);

        // pocet bojovnikov v armade
        auto pocet = armada->pocetBojovnikov(armada->getHlava());
        std::cout << "Pocet bojovnikov: " << pocet << std::endl;

        // zmeraj vzdialenost bojovnikov
        auto vzdialenost = armada->vzdialenostBojovnikov(armada->getChvost(), armada->getHlava());
        std::cout << "Vzdialenost bojovnikov chvost-hlava: " << vzdialenost << std::endl;
        vzdialenost = armada->vzdialenostBojovnikov(armada->getHlava(), armada->getChvost());
        std::cout << "Vzdialenost bojovnikov hlava-chvost: " << vzdialenost << std::endl;

        // vybijanie bojovnikov
        int M;
        std::cout << "Zadajte po kolko sa odpocitavaju: ";
        std::cin >> M;
        auto bojovnik = armada->vybiBojovnikov(M);
        std::cout << "Posledny zostal " << bojovnik->getId() << ". bojovnik" << std::endl << std::endl;

        // pocet bojovnikov v armade
        pocet = armada->pocetBojovnikov(armada->getHlava());
        std::cout << "Pocet bojovnikov: " << pocet << std::endl;

        // zmeraj vzdialenost bojovnikov
        vzdialenost = armada->vzdialenostBojovnikov(armada->getChvost(), armada->getHlava());
        std::cout << "Vzdialenost bojovnikov chvost-hlava: " << vzdialenost << std::endl;
        vzdialenost = armada->vzdialenostBojovnikov(armada->getHlava(), armada->getChvost());
        std::cout << "Vzdialenost bojovnikov hlava-chvost: " << vzdialenost << std::endl;

        delete armada;  // uvolni pamat

        return 0;
    }