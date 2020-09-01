#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>
using namespace std;

struct item
{
    char nume[30];
    int ind1,ind2;
};

class Agent
{
  public:
    int putere;
    int viata;
    bool cutitul_mortii;
    int linie,coloana;

    Agent() {}
    virtual ~Agent() {}
    virtual int get_putere() const = 0;
    virtual void set_putere(int x)= 0;
    virtual int get_viata() const = 0;
    virtual void set_viata(int x)= 0;
    virtual int get_linie() const = 0;
    virtual int get_coloana() const = 0;
    virtual void PrimesteAbilitate(vector<item>&)= 0;
    virtual void Actualizare_Pozitie(char**)= 0;
    virtual void MutareAgent(char**,int,vector<Agent*>&, int&, int&) = 0;
    virtual Agent* Battle(vector<Agent*>&,int, int, int) =0;
};

class AgentA: public Agent
{
public:
    AgentA()
    {
        putere=200;
        viata=4;
        cutitul_mortii=false;
        linie=-1;
        coloana=-1;
    }
    int get_putere() const
    {
        return putere;
    }
    void set_putere(int x)
    {
        putere = x;
    }
    int get_viata() const
    {
        return viata;
    }
    void set_viata(int x)
    {
        viata =x;
    }
    int get_linie() const
    {
        return linie;
    }
    int get_coloana() const
    {
        return coloana;
    }

    void PrimesteAbilitate(vector<item> &items)
    {
        for(int i=0;i<items.size();i++)
            {
                if(linie==items[i].ind1 && coloana == items[i].ind2)
                {
                    if(strcmp(items[i].nume,"Cutitul_mortii")==0) cutitul_mortii=true;
                    else if(strcmp(items[i].nume,"Elixirul_puterii")==0 ) putere=putere+50;
                    else if(strcmp(items[i].nume,"Scutul_vietii")==0) viata=viata+1;
                    items.erase(items.begin()+i);
                    cout<<"Agentul de pe pozitia: "<<linie<<" "<<coloana<<"a primit item."<<endl;
                    break;
                }
            }
    }
    void MutareAgent(char ** Harta, int dimensiune,vector<Agent*> &agenti,int &ind_l, int &ind_c)
    {
        Harta[linie][coloana]='*';
        int copie_linie=linie;
        int copie_coloana= coloana;
        if(copie_linie < dimensiune-1)
        {
            copie_linie++;
        }
        else if(copie_coloana < dimensiune-1)
        {
            copie_linie=0;
            copie_coloana++;
        }
        else
        {
            copie_linie = 0;
            copie_coloana = 0;
        }

        if(Harta[copie_linie][copie_coloana]=='*'|| Harta[copie_linie][copie_coloana] =='X'|| Harta[copie_linie][copie_coloana] =='P'|| Harta[copie_linie][copie_coloana]=='V')
        {
                linie=copie_linie;
                coloana=copie_coloana;

                Harta[linie][coloana]='A';

                for(Agent* aux:agenti)
                    if(aux==this)
                    {
                        aux->linie=linie;
                        aux->coloana=coloana;
                    }
        }

        ind_l=copie_linie;
        ind_c=copie_coloana;

    }

    void Actualizare_Pozitie(char ** Harta)
    {
         Harta[linie][coloana]='A';
    }

   Agent* Battle(vector<Agent*> &agenti,int indice_luptator,int ind_l, int ind_c)
    {
       cout<<"Batalie intre agentul cu nr. "<<indice_luptator<<" si agentul cu nr. ";
       int indice_adversar=-1;
       int ok=1;
        for(Agent* aux:agenti)
        {
            indice_adversar++;
            if(ind_l==aux->linie && ind_c==aux->coloana)
            {
                cout<<indice_adversar<<endl;
                int putere_adversar=aux->putere;
                int putere_luptator=putere;
                if(cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        cutitul_mortii=false;
                        return this;
                    }
                    else if(aux->cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        aux->cutitul_mortii=false;
                        return aux;
                    }
                while(ok!=0)
                {
                    if(putere >= aux->putere && viata>0 && aux->viata>0)
                    {
                        aux->viata--;
                        aux->putere/=2;
                        putere/=3;
                    }
                    else
                    {
                        viata--;
                        aux->putere/=2;
                        putere/=2;
                    }
                    if(viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        ok=0;
                        return aux;
                    }
                    if(aux->viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        ok=0;
                        return this;
                    }

                }
            }
        }
    }
    ~AgentA() {}
};

class AgentB: public Agent
{
public:
    AgentB()
    {
        putere=150;
        viata=3;
        cutitul_mortii=false;
        linie=-1;
        coloana=-1;
    }
    int get_putere() const
    {
        return putere;
    }
    void set_putere(int x)
    {
        putere = x;
    }
    int get_viata() const
    {
        return viata;
    }
    void set_viata(int x)
    {
        viata =x;
    }
    int get_linie() const
    {
        return linie;
    }
    int get_coloana() const
    {
        return coloana;
    }
    void MutareAgent(char ** Harta, int dimensiune,vector<Agent*> &agenti,int &ind_l,int &ind_c)
    {
        Harta[linie][coloana]='*';
        int copie_linie=linie;
        int copie_coloana=coloana;
        if(copie_linie % 2 ==0 && copie_linie < dimensiune - 1)
        {
            if(copie_coloana < dimensiune- 1 ) copie_coloana ++;
            else if(copie_coloana == dimensiune - 1) copie_linie ++;
        }
        else if(copie_linie % 2 ==1 && copie_linie < dimensiune - 1)
        {
            if(copie_coloana > 0) copie_coloana --;
            else if(copie_coloana == 0 ) copie_linie ++;
        }
        else if(copie_linie % 2 ==0 && copie_linie == dimensiune - 1)
        {
            if(copie_coloana < dimensiune - 1) copie_coloana ++;
            else if(copie_coloana == dimensiune - 1) copie_coloana = copie_linie = 0;
        }
        else if(copie_linie % 2 ==1 && copie_linie == dimensiune - 1)
        {
            if(copie_coloana > 0) copie_coloana --;
            else if(copie_coloana == 0) copie_coloana = copie_linie = 0;
        }

        if(Harta[copie_linie][copie_coloana]== '*' || Harta[copie_linie][copie_coloana] =='X' || Harta[copie_linie][copie_coloana] =='P'|| Harta[copie_linie][copie_coloana] =='V')
        {
            linie=copie_linie;
            coloana=copie_coloana;
            Harta[linie][coloana]='B';
            for(Agent* aux:agenti)
            if(aux==this)
            {   aux->linie=linie;
                aux->coloana=coloana;
            }
        }

        ind_l=copie_linie;
        ind_c=copie_coloana;

    }

    void PrimesteAbilitate(vector<item> &items)
    {
        for(int i=0;i<items.size();i++)
            {
                if(linie==items[i].ind1 && coloana == items[i].ind2)
                {
                    if(strcmp(items[i].nume,"Cutitul_mortii")==0) cutitul_mortii=true;
                    else if(strcmp(items[i].nume,"Elixirul_puterii")==0 ) putere=putere+50;
                    else if(strcmp(items[i].nume,"Scutul_vietii")==0) viata=viata+1;
                    items.erase(items.begin()+i);
                    cout<<"Agentul de pe pozitia: "<<linie<<" "<<coloana<<"a primit item."<<endl;
                    break;
                }
            }
    }

    void Actualizare_Pozitie(char ** Harta)
    {
         Harta[linie][coloana]='B';
    }

   Agent* Battle(vector<Agent*> &agenti,int indice_luptator,int ind_l, int ind_c)
    {
        cout<<"Batalie intre agentul cu nr. "<<indice_luptator<<" si agentul cu nr. ";
        int indice_adversar=-1;
        int ok=1;
        for(Agent* aux:agenti)
        {
            indice_adversar++;
            if(ind_l==aux->linie && ind_c==aux->coloana)
            {
                cout<<indice_adversar<<endl;
                int putere_adversar=aux->putere;
                int putere_luptator=putere;
                if(cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        cutitul_mortii=false;
                        return this;
                    }
                    else if(aux->cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        aux->cutitul_mortii=false;
                        return aux;
                    }
                while(ok!=0)
                {
                    if(putere >= aux->putere && viata>0 && aux->viata>0)
                    {
                        aux->viata--;
                        aux->putere/=2;
                        putere/=3;
                    }
                    else
                    {
                        viata--;
                        aux->putere/=2;
                        putere/=2;
                    }
                    if(viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        return aux;
                        ok=0;
                    }
                    if(aux->viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        return this;
                        ok=0;
                    }

                }
            }
        }
    }
    ~AgentB() {}
};

class AgentC: public Agent
{
public:
    AgentC()
    {
        putere=100;
        viata=2;
        cutitul_mortii=false;
        linie=-1;
        coloana=-1;
    }
    int get_putere() const
    {
        return putere;
    }
    void set_putere(int x)
    {
        putere = x;
    }
    int get_viata() const
    {
        return viata;
    }
    void set_viata(int x)
    {
        viata =x;
    }

    int get_linie() const
    {
        return linie;
    }

    int get_coloana() const
    {
        return coloana;
    }

     void MutareAgent(char ** Harta, int dimensiune,vector<Agent*> &agenti,int &ind_l,int &ind_c)
    {
        Harta[linie][coloana]='*';
        int copie_linie=linie;
        int copie_coloana=coloana;
        if(copie_linie < dimensiune - 1)
        {
            if(copie_coloana < dimensiune - 1) copie_coloana ++;
            else if(copie_coloana == dimensiune - 1) {copie_linie++; copie_coloana = 0;}
        }
        else if(copie_linie == dimensiune-1)
        {
            if(copie_coloana < dimensiune - 1) copie_coloana ++;
            else if(copie_coloana == dimensiune - 1) {copie_linie=0; copie_coloana = 0;}
        }

        if(Harta[copie_linie][copie_coloana]== '*' || Harta[copie_linie][copie_coloana] =='X' || Harta[copie_linie][copie_coloana] =='P'|| Harta[copie_linie][copie_coloana] =='V')
        {
            linie=copie_linie;
            coloana=copie_coloana;
            Harta[linie][coloana]='C';
            for(Agent* aux:agenti)
                if(aux==this)
                {
                    aux->linie=linie;
                    aux->coloana=coloana;
                }
        }

        ind_l=copie_linie;
        ind_c=copie_coloana;
    }

    void PrimesteAbilitate(vector<item> &items)
    {
        for(int i=0;i<items.size();i++)
            {
                if(linie == items[i].ind1 && coloana == items[i].ind2)
                {
                    if(strcmp(items[i].nume,"Cutitul_mortii")==0) cutitul_mortii=true;
                    else if(strcmp(items[i].nume,"Elixirul_puterii")==0 ) putere=putere+50;
                    else if(strcmp(items[i].nume,"Scutul_vietii")==0) viata=viata+1;
                    items.erase(items.begin()+i);
                    cout<<"Agentul de pe pozitia: "<<linie<<" "<<coloana<<"a primit item."<<endl;
                    break;
                }
            }
    }
    void Actualizare_Pozitie(char ** Harta)
    {
         Harta[linie][coloana]='C';
    }

   Agent* Battle(vector<Agent*> &agenti,int indice_luptator,int ind_l, int ind_c)
    {
        cout<<"Batalie intre agentul cu nr. "<<indice_luptator<<" si agentul cu nr. ";
        int indice_adversar=-1;
        int ok=1;
        for(Agent* aux:agenti)
        {
            indice_adversar++;
            if(ind_l==aux->linie && ind_c==aux->coloana)
            {
                cout<<indice_adversar<<endl;
                int putere_adversar=aux->putere;
                int putere_luptator=putere;
                if(cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        cutitul_mortii=false;
                        return this;
                    }
                    else if(aux->cutitul_mortii==1)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        aux->cutitul_mortii=false;
                        return aux;
                    }
                while(ok!=0)
                {
                    if(putere >= aux->putere && viata>0 && aux->viata>0)
                    {
                        aux->viata--;
                        aux->putere/=2;
                        putere/=3;
                    }
                    else
                    {
                        viata--;
                        aux->putere/=2;
                        putere/=2;
                    }
                    if(viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_luptator);
                        return aux;
                        ok=0;
                    }
                    if(aux->viata==0)
                    {
                        agenti.erase(agenti.begin()+indice_adversar);
                        linie=ind_l;
                        coloana=ind_c;
                        return this;
                        ok=0;
                    }

                }
            }
        }
    }
    ~AgentC() {}
};

class Game
{
    int dimensiune;
    int nr_agenti;
    int nr_items;
    char **Harta;
    vector<Agent*> agenti;
    vector<item> items;
public:
    Game()
    {
        dimensiune=15;
        nr_agenti=21;
        nr_items=20;
        Harta= new char*[dimensiune];
        for(int i=0; i<dimensiune; i++)
            Harta[i]=new char[dimensiune];
        for(int i=0; i<dimensiune; i++)
            for(int j=0; j<dimensiune; j++)
                Harta[i][j]='*';
    }
    int get_dimensiune()
    {
        return dimensiune;
    }
    void set_dimensiune(int x)
    {
        dimensiune =x;
    }
    int get_nr_agenti()
    {
        return agenti.size();
    }
    void set_nr_agenti(int x)
    {
        nr_agenti=x;
    }
    friend ostream &operator<<(ostream &,const Game&);
    void Generator_Agenti()
    {
        srand(time(NULL));
        while(agenti.size()!= nr_agenti)
        {
            int tip=rand()%3;
            if(tip==0)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                Agent* ptr = new AgentA;
                ptr->linie=x;
                ptr->coloana=y;
                agenti.push_back(ptr);
                Harta[x][y]='A';
                //cout<<"Agent A pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
            if(tip==1)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                Agent* ptr = new AgentB;
                ptr->linie=x;
                ptr->coloana=y;
                agenti.push_back(ptr);
                Harta[x][y]='B';
                //cout<<"Agent B pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
            if(tip==2)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                Agent* ptr = new AgentC;
                ptr->linie=x;
                ptr->coloana=y;
                agenti.push_back(ptr);
                Harta[x][y]='C';
                //cout<<"Agent C pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
        }
    }
    void Generator_items()
    {
        item abilitate;
        srand(time(NULL));
        while(items.size()!= nr_items)
        {
            int tip=rand()%3;
            if(tip==0)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                abilitate.ind1=x;
                abilitate.ind2=y;
                strcpy(abilitate.nume,"Cutitul_mortii");
                items.push_back(abilitate);
                Harta[x][y]='X';
              //  cout<<"Cutitul mortii pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
            if(tip==1)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                abilitate.ind1=x;
                abilitate.ind2=y;
                strcpy(abilitate.nume,"Scutul_vietii");
                items.push_back(abilitate);
                Harta[x][y]='V';
              //  cout<<"Scutul vietii pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
            if(tip==2)
            {
                int x=rand()%dimensiune;
                int y=rand()%dimensiune;
                while(Harta[x][y]!='*')
                {
                    x=rand()%dimensiune;
                    y=rand()%dimensiune;
                }
                abilitate.ind1=x;
                abilitate.ind2=y;
                strcpy(abilitate.nume,"Elixirul_puterii");
                items.push_back(abilitate);
                Harta[x][y]='P';
                //cout<<"Elixirul puterii pe linia:"<<x<<" si coloana:"<<y<<endl;
            }
        }
    }
    void afisare_agenti()
    {
        int indice=-1;
          for(Agent*a: agenti)
          {
              indice++;
            cout<<indice<<".Agent cu puterea: "<<a->putere<<" viata: "<<a->viata<<" cutit: "<<a->cutitul_mortii<<" pe linia: "<<a->linie<<" si coloana: "<<a->coloana<<endl;
          }
    }
    void afisare_items()
    {
        for(int i=0;i<items.size();i++)
            cout<<items[i].nume<<" pe linia: "<<items[i].ind1<<" si coloana: "<<items[i].ind2<<endl;
    }
    void Run()
    {
        int poz_l,poz_c;
        for(int i=0; i<dimensiune; i++)
            for(int j=0; j<dimensiune; j++)
            {
                if(Harta[i][j]=='A' || Harta[i][j]=='B' || Harta[i][j]=='C')
                {
                    poz_l=i;
                    poz_c=j;
                    int indice_luptator=-1;
                    for(Agent* a: agenti)
                    {
                        indice_luptator++;
                        int ind_l,ind_c;
                        Agent* castigator=NULL;
                        afisare_agenti();
                        cout<<endl;
                        cout<<"initial:"<<endl;

                        for(int i=0; i<dimensiune; i++)
                        {
                            for(int j=0; j<dimensiune; j++)
                                cout<<Harta[i][j]<<" ";
                            cout<<endl;
                        }
                    cout<<endl;

                    if(a->linie==poz_l && a->coloana==poz_c)
                    {   while(!castigator && nr_agenti>1)
                        {a->MutareAgent(Harta,dimensiune,agenti,ind_l,ind_c);
                         a->PrimesteAbilitate(items);
                        if(a->linie != ind_l || a->coloana != ind_c)
                        {
                            castigator=a->Battle(agenti,indice_luptator,ind_l,ind_c);
                            castigator->Actualizare_Pozitie(Harta);
                            nr_agenti--;

                            cout<<endl;
                            cout<<"dupa batalie: "<<endl;
                            for(int i=0; i<dimensiune; i++)
                            {
                                for(int j=0; j<dimensiune; j++)
                                    cout<<Harta[i][j]<<" ";
                                cout<<endl;
                            }
                        cout<<endl;
                        afisare_agenti();
                        cout<<endl;
                        }
                        else
                        {
                            cout<<endl;
                            cout<<"dupa mutare: "<<endl;
                            for(int i=0; i<dimensiune; i++)
                            {
                                for(int j=0; j<dimensiune; j++)
                                    cout<<Harta[i][j]<<" ";
                                cout<<endl;
                            }
                            cout<<endl;
                        }
                    }
                    }
                    }
                }
            }

    }

};

ostream &operator<<(ostream &out,const Game&g)
{

    for(int i=0; i<g.dimensiune; i++)
    {
        for(int j=0; j<g.dimensiune; j++)
               out<<g.Harta[i][j]<<" ";
        out<<endl;
    }
    return out;

}


int main()
{
    Game g;
    g.Generator_Agenti();
    g.Generator_items();
    cout<<endl;
    g.afisare_items();
    cout<<endl;
   // g.afisare_agenti();
    cout<<endl;
    cout<<g;
    cout<<endl;
  //  cout<<g.get_dimensiune()<<endl;
    //cout<<g.get_nr_agenti()<<endl;
    while(g.get_nr_agenti()!= 1) g.Run();
    //cout<<g;
    cout<<endl;
   g.afisare_agenti();
   cout<<endl;
   g.afisare_items();

    return 0;
}

