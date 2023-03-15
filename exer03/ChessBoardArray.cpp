#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray {
       protected:

         class Row {
           public:

             Row(ChessBoardArray &a, int i)
               : chess_Board_Array(a), row(i) {}

             int & operator [] (int i) const { return chess_Board_Array.select(row,i); }

           private:
             ChessBoardArray &chess_Board_Array;
             int row;
         };

         class ConstRow {
           public:

             ConstRow(const ChessBoardArray &a, int i)
               : chess_Board_Array(a), row(i) {}

             int operator [] (int i) const { return chess_Board_Array.select(row,i); }

           private:
             const ChessBoardArray &chess_Board_Array;
             int row;
         };

       public:

         ChessBoardArray(unsigned size = 0, unsigned base = 0) {
           data = new int[(size * size+1)/2];
           Base = base;
           Size = size;
           for(unsigned i = 0; i < (Size * Size +1)/2; i++) data[i] = 0;
          }

          ChessBoardArray(const ChessBoardArray &a) {
           data = new int[(a.Size * a.Size +1)/2];
           Base = a.Base;
           Size = a.Size;
           for(unsigned i = 0; i < (Size * Size +1)/2; i++)
             data[i] = a.data[i];
         }

         ~ChessBoardArray() {
           delete []data;
         }

         ChessBoardArray & operator = (const ChessBoardArray &a) {
           delete []data;
           Base = a.Base;
           Size = a.Size;
           data = new int[(Size * Size +1)/2];
           for(unsigned i = 0; i < (Size * Size +1)/2; i++)
             data[i] = a.data[i];
           return *this;
         }

         int & select(int i, int j) { return data[loc(i,j)]; }
         int select(int i, int j) const { return data[loc(i,j)]; }

         const Row operator [] (int i) { return  Row(*this,i); }
         const ConstRow operator [] (int i) const { return ConstRow(*this,i); }

         friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
           for(unsigned  i = a.Base; i < (a.Size + a.Base); i++) {
             for(unsigned j = a.Base; j < (a.Size + a.Base); j++) {
               try { cout<< setw(4) << a.select(i,j); }
               catch(out_of_range &e) { cout << setw(4) << 0; }
            }
             cout << endl;
           }
           return out;
         }

          private:

         int *data;
         int Base;
         unsigned  Size;

         unsigned int loc(int i, int j) const throw(out_of_range) {
           int di = i - Base, dj = j - Base;
           if( di < 0 || di >= Size || dj < 0 || dj >= Size ) throw out_of_range("invalid index");
           if(  ( di % 2 != 0 && dj % 2 == 0 ) || ( di % 2 == 0 && dj % 2 != 0 ) )  throw out_of_range("invalid index");
           return ( (di*Size + dj) /2 );
         }
};