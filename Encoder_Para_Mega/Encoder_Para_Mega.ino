volatile int contador=0;   // Declaramos como 'volatile' las variables que participan dentro y fuera
                           //   de la interrupción.
byte ant=0, act=0;         // Sólo se utiliza los dos primeros bits de estas variables.
                            //  ant=anterior, act=actual.
int  n=0;                  // Variable auxiliar para notar cambios en el contador.

void setup()
{
    Serial.begin(115200);  // Dará la posición por el terminal serie.
    /*
    pinMode(2, INPUT);     // No es necesario declarar pinMode, "attachInterrupt" se encarga de
                              convertir en entrada, pero
    pinMode(3, INPUT);     // los puedes poner si quieres. Los pines 2 y 3 es donde va conectado el
                              encoder incremental.
    */
    attachInterrupt(digitalPinToInterrupt(20), encoder, CHANGE); // En cualquier flanco ascendente o
                                                                //  descendente
    attachInterrupt(digitalPinToInterrupt(21), encoder, CHANGE); // en los pines 2 y 3 actúa la
                                                                  // interrupción.
}
void loop()
{
    if(n != contador)      // Sólo cuando la variable contador cambie de valor se
                           //   transmite dicho valor.
    {
        n=contador;
        Serial.println(contador);
    }
}

void encoder() 
{            
    ant=act;                                                   // Guardamos 'act' para convertirlo
                                                               //   en pasado.
    if(digitalRead(20)==1) bitSet(act,0); else bitClear(act,0); // Seteamos los dos primeros bits
                                                                //  de la variable 'act' con
    if(digitalRead(21)==1) bitSet(act,1); else bitClear(act,1); // el valor de este instante, como
                                                                //  un número de dos bits.
       
    if(ant==3 && act==1) contador++;
    if(ant==1 && act==0) contador++;
    if(ant==0 && act==2) contador++;
    if(ant==2 && act==3) contador++;
       
    if(ant==1 && act==3) contador--;
    if(ant==0 && act==1) contador--;
    if(ant==2 && act==0) contador--;
    if(ant==3 && act==2) contador--;
}
