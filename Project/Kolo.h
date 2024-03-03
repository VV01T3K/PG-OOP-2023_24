#include "FiguraPlaska.h"
class Kolo : public FiguraPlaska {
    double r;

   protected:
    void Wypisz(std::ostream& out) const override;

   public:
    Kolo(double r);
    double GetR() const;
    void SetR(double a);
    double Obwod() override;
    double Pole() override;

    ~Kolo() override;

   private:
};