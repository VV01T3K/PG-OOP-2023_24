_Pragma("once");
#include "FiguraPlaska.h"

class Trapez : public FiguraPlaska {
   private:
    double a, b, c, d, h;

   protected:
    void Wypisz(std::ostream& out) const override;

   public:
    // podstawa 1 , podstawa 2, bok 1, bok 2, wysokosc
    Trapez(double a, double b, double c, double d, double h);
    double GetA() const;
    void SetA(double a);
    double GetB() const;
    void SetB(double b);
    double GetC() const;
    void SetC(double c);
    double GetD() const;
    void SetD(double d);
    double GetH() const;
    void SetH(double h);
    double Obwod() override;
    double Pole() override;

    ~Trapez() override;
};
