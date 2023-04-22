#ifndef _MACHINE_STATE_H_
#define _MACHINE_STATE_H_


enum states {search, attack, rotate};
states get_state(double left_sensor, double right_sensor, double front_sensor, int left_line, int right_line, long rotate_start_time);
int ajuste_sumonado(double left_sensor, double right_sensor, double front_sensor);
void rotacionar();
void procurar();
void atacar(int valor_ajustado);


#endif