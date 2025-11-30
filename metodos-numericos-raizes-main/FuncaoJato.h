#ifndef FUNCAOJATO_H
#define FUNCAOJATO_H

class FuncaoJato {
private:
    double a; // parâmetro de ajuste

public:
    FuncaoJato(double parametro_a);
    
    // Função f(d) = a*d - d*ln(d)
    double calcular(double d) const;
    
    // Derivada f'(d) = a - ln(d) - 1 (para Newton-Raphson)
    double calcularDerivada(double d) const;
    
    double getParametroA() const;
    void setParametroA(double novo_a);
};

#endif // FUNCAOJATO_H

