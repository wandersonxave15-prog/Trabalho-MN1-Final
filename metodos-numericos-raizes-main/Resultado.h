#ifndef RESULTADO_H
#define RESULTADO_H

class Resultado {
private:
    double raiz;
    double erro;
    int iteracoes;
    bool convergiu;

public:
    Resultado();
    Resultado(double r, double e, int it, bool conv);
    
    double getRaiz() const;
    double getErro() const;
    int getIteracoes() const;
    bool getConvergiu() const;
    
    void setRaiz(double r);
    void setErro(double e);
    void setIteracoes(int it);
    void setConvergiu(bool conv);
};

#endif

