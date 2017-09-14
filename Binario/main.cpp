#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

class Binaria{
public:
    int tam;
    int bit;
    int entero;
    int *p;
    Binaria()
    {
        tam=4;
        p=new int[tam];
        for(int i=0;i<tam;i++)
            p[i]=0;
    }

    Binaria(int tam_)
    {
        tam=tam_;
        p=new int[tam_];
        cout<<"Ingrese 0 o 1\n";
        for(int i=0;i<tam_;i++)
        {
            cin>>bit;
            p[i]=bit;
        }
        cout<<"Binario: ";
        for(int i=0;i<tam_;i++)
        {
            cout<<p[i];
        }
        cout<<endl;
        int n=0;
        entero=0;
        for(int i=tam_-1;i>0;i--)
        {
            entero+= pow(2,n)*p[i];
            n++;
        }
        if(p[0]==1)
            entero-=pow(2,n)*p[0];
        cout<<"\nEntero: "<<entero<<endl;
    }
    /*
    Binaria ( const Binaria &A)
    {
        Binaria resul;
        resul.tam=A.tam;
        resul.entero=A.entero;
        resul.p=new int [A.tam];
        for(int i=0;i<A.tam;i++)
        {
            resul.p[i]=A.p[i];
        }
        return resul;
    }*/

    void agrandar(int tam_)
    {
        cout<<"Se necesite igualar el tamaño\n";
        int *temp=new int[tam_];

        for(int i=0;i<tam_;i++)
        {
            if(i<tam)
            {
                if(p[0]==1)
                    temp[i]=1;
                else
                    temp[i]=0;
            }
            else
            {
                temp[i]=p[i-tam+1];
            }
        }

        delete[] p;
        tam=tam_;
        p=temp;
    }

     void cambio()
    {
        int acarreo=0;
        for(int i=0;i<tam;i++)
            (p[i]==0)?p[i]=1:p[i]=0;
        for(int i=tam-1;i>=0;i--)
        {
            p[i] = p[i] ^ 1;
            p[i] = p[i] ^ acarreo;

            if( p[i]==1 or acarreo==1)
            {
                acarreo=1;
            }
            else
            {
                acarreo=0;
            }
        }
        cout<<"Cambio de signo: ";
        for(int i=0;i<tam;i++)
            cout<<p[i];
    }

    void shift(int a)
    {
        int *temp=new int[tam];
        temp[0]=a;
        for(int i=1;i<tam;i++)
            temp[i]=p[i-1];
        for(int i=0;i<tam;i++)
            cout<<temp[i];
        delete[] p;
        p = temp;
    }

    int sumar(Binaria &M)
    {
        int x;
        int acarreo=0;
        int c=0;
        cout<<"\n     ";
        for(int i=0;i<tam;i++)
            cout<<p[i]<<" ";
        for(int i=tam-1;i>=0;i--)
        {
            x=p[i];
            p[i] = p[i] ^ M.p[i];
            p[i] = p[i] ^ acarreo;

            if(  x==1 and  M.p[i]==1 )
            {
                acarreo=1;
            }
            else if( (acarreo==1) and ( x==1 or M.p[i]==1 ) )
                acarreo=1;
            else
                acarreo=0;
        }
        cout<<"\n   + ";
        for(int i=0;i<M.tam;i++)
            cout<<M.p[i]<<" ";
        cout<<"\n     _________";
        cout<<"\n     ";
        for(int i=0;i<tam;i++)
            cout<<p[i]<<" ";

        return acarreo;
        cout<<endl<<endl;
    }

    void resta(Binaria &M);
    {
        M.cambio();
        int x;
        int acarreo=0;
        int c=0;
        cout<<"\n     ";
        for(int i=0;i<tam;i++)
            cout<<p[i]<<" ";
        for(int i=tam-1;i>=0;i--)
        {
            x=p[i];
            p[i] = p[i] ^ M.p[i];
            p[i] = p[i] ^ acarreo;

            if(  x==1 and  M.p[i]==1 )
            {
                acarreo=1;
            }
            else if( (acarreo==1) and ( x==1 or M.p[i]==1 ) )
                acarreo=1;
            else
                acarreo=0;
        }
        cout<<"\n   + ";
        for(int i=0;i<M.tam;i++)
            cout<<M.p[i]<<" ";
        cout<<"\n     _________";
        cout<<"\n     ";
        for(int i=0;i<tam;i++)
            cout<<p[i]<<" ";

    }

    friend Binaria operator-(Binaria &a, Binaria &b)
    {
        b.cambio();
        cout<<endl;
        int acarreo=0;
        Binaria result;
        if(a.tam>b.tam)
        {
            result.tam=a.tam;
            b.agrandar(a.tam);
        }
        else
        {
            result.tam=b.tam;
            a.agrandar(b.tam);
        }
        result.p=new int[a.tam];

        for(int i=a.tam-1;i>=0;i--)
        {
            result.p[i]=a.p[i] ^ b.p[i];
            result.p[i] = result.p[i] ^ acarreo;

            if( ( a.p[i]==1 and  b.p[i]==1 ) or acarreo==1)
            {
                acarreo=1;
            }
            else
            {
                acarreo=0;
            }
        }

        cout<<"\n     ";
        for(int i=0;i<a.tam;i++)
            cout<<a.p[i]<<" ";

        cout<<"\n   + ";
        for(int i=0;i<b.tam;i++)
            cout<<b.p[i]<<" ";
        cout<<"\n     _________";
        cout<<"\n     ";
        for(int i=0;i<result.tam;i++)
            cout<<result.p[i]<<" ";
        cout<<endl<<endl;
        return result;
    }

    friend Binaria operator*(Binaria &Q, Binaria &M)
    {
        int c=0;
        Binaria A=M;
        cout<<"\nShift A: ";
        A.shift(0);
        cout<<"\nShift Q: ";
        Q.shift(1);
        cout<<endl;
        for(int i=1;i<M.tam;i++)
        {
            cout<<"Paso Numero: "<<i+1<<endl;
            cout<<endl<<endl;

            if(M.p[i]==1)
            {
                c=A.sumar(M);
                cout<<"C: "<<c<<endl;
            }
            cout<<"\nShift A: ";
            A.shift(c);
            cout<<"\nShift Q: ";
            Q.shift(1);
/*            else
            {
                cout<<"\nShift A: ";
                A.shift(c);
                cout<<"\nShift Q: ";
                Q.shift(1);
            }
*/            cout<<endl;
        }
        return A;
    }

    friend Binaria operator/(Binaria &Q, Binaria &M)
    {
        Binaria A=Q;
        Binaria temp=M;
        temp.cambio();

        return Q;
    }

     ~Binaria ()
    {
        delete[] p;
    }

};

int main()
{
    int n;
    cout<<"Ingreso la cantidad de bits--> "; cin>>n;
    Binaria a(n);
    Binaria b(n);
    Binaria c=a/b;
    return 0;
}
