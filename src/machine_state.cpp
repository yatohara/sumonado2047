#include "machine_state.h"
#include "setup_motores.h"
#define DIST 125



// funcoes presente
states get_state(double left_sensor, double right_sensor, double front_sensor, int left_line, int right_line, long rotate_start_time);
int ajuste_sumonado(double left_sensor, double right_sensor, double front_sensor);
void rotacionar();
void procurar();
void atacar(int valor_ajustado);

// funcao para ler os valores dos sensores e retornar o estado que o sumonado deve estar
states get_state(double left_sensor, double right_sensor, double front_sensor, int left_line, int right_line, long rotate_start_time){

    if ((front_sensor <= DIST) || (left_sensor <= DIST) || (right_sensor <= DIST)){
        return attack;
    }

    else if ((left_line == 0) || (right_line == 0)){
        return rotate;
    }

    else if (millis() - rotate_start_time < 500){
        return rotate;
    }

    return search;
}

int ajuste_sumonado(double left_sensor, double right_sensor, double front_sensor){
    
    bool clear_front = front_sensor > DIST;
    bool clear_left = left_sensor > DIST;
    bool clear_right = right_sensor > DIST;

    bool opponent_left = ((clear_front) && (clear_right));
    bool opponent_right = ((clear_front) && (clear_left));

    if (opponent_right){
        return 1;
    }

    else if (opponent_right){
        return -1;
    }

    return 0;
}


void rotacionar(){
    set_speed(255, 255);
}

void procurar(){
    set_speed(-255, 255);
}

void atacar(int valor_ajustado){
/*     if (valor_ajustado == 1){
        set_speed(255, 200);
    }
    else if (valor_ajustado == -1){
        set_speed(200, 255);
    }
    else{
        set_speed(255, 255);
    } */
    // set_speed(-255, 255);

}
