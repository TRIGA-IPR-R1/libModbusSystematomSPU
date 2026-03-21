/*
libModbusSystematomSPU is a library to communicate with the SystemAtom SPU
using MODBUS-RTU (RS-485) on a GNU operating system.
Copyright (C) 2023-2024  Thalles Campagnani

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <vector>

struct SPU_DATA
{
    int   STATE             = -1;   //Status da SPU:
                                    //-1 = Nenhuma tentativa de conexão realizada ainda.
                                    // 0 = Valores lidos com sucesso.
                                    // 1 = Erro ao ler dados.
                                    // 2 = Erro de contexto modbus (provavelmente não existe dispositivo USB).
    std::chrono::system_clock::time_point TIME;
    float   N_DATA_FP       = -1;
    float   T_DATA_FP       = -1;
    float   F1_DATA_FP      = -1;
    float   F2_DATA_FP      = -1;
    float   F3_DATA_FP      = -1;
    float   EMR_N_THRESHOLD = -1;
    float   WRN_N_THRESHOLD = -1;
    float   EMR_T_THRESHOLD = -1;
    float   WRN_T_THRESHOLD = -1;
    int     EMR_N           = -1;
    int     WRN_N           = -1;
    int     EMR_T           = -1;
    int     WRN_T           = -1;
    int     R1              = -1;
    int     R2              = -1;
    int     R3              = -1;
    int     RDY             = -1;
    int     TEST            = -1;
    int     XXXX            = -1;
};

// Matriz Nx2: 
// Coluna 0 (Índice 0) = Header
// Coluna 1 (Índice 1) = Tipo
std::vector<std::vector<std::string>> SPU_DATA_MATRIX = {
    {"SPU_%s_STATE",           "%d"},
    {"SPU_%s_TIME_Y",          "%d"},
    {"SPU_%s_TIME_Mo",         "%d"},
    {"SPU_%s_TIME_D",          "%d"},
    {"SPU_%s_TIME_H",          "%d"},
    {"SPU_%s_TIME_Mi",         "%d"},
    {"SPU_%s_TIME_S",          "%d"},
    {"SPU_%s_TIME_MS",         "%d"},
    {"SPU_%s_N_DATA_FP",       "%f"},
    {"SPU_%s_T_DATA_FP",       "%f"},
    {"SPU_%s_F1_DATA_FP",      "%f"},
    {"SPU_%s_F2_DATA_FP",      "%f"},
    {"SPU_%s_F3_DATA_FP",      "%f"},
    {"SPU_%s_EMR_N_THRESHOLD", "%f"},
    {"SPU_%s_WRN_N_THRESHOLD", "%f"},
    {"SPU_%s_EMR_T_THRESHOLD", "%f"},
    {"SPU_%s_WRN_T_THRESHOLD", "%f"},
    {"SPU_%s_EMR_N",           "%d"},
    {"SPU_%s_WRN_N",           "%d"},
    {"SPU_%s_EMR_T",           "%d"},
    {"SPU_%s_WRN_T",           "%d"},
    {"SPU_%s_R1",              "%d"},
    {"SPU_%s_R2",              "%d"},
    {"SPU_%s_R3",              "%d"},
    {"SPU_%s_RDY",             "%d"},
    {"SPU_%s_TEST",            "%d"},
    {"SPU_%s_XXXX",            "%d"}
};

void libModbusSystematomSPU_license();

struct libModbusSystematomSPU_private;

class libModbusSystematomSPU {
public:
    libModbusSystematomSPU(std::string portname);
    ~libModbusSystematomSPU();

    bool tryConnect();
    
    //Get the name of the port (who am I?)
    std::string  get_portname();

    //Get all the struct and update all (or part) of the variables
    SPU_DATA get_all             ();
    SPU_DATA get_all_update_NT   ();
    SPU_DATA get_all_update_F    ();
    SPU_DATA get_all_update_NTF  ();
    SPU_DATA get_all_update_bool ();

    //Get just variable
    float get_N_DATA_FP          ();
    float get_T_DATA_FP          ();
    float get_F1_DATA_FP         ();
    float get_F2_DATA_FP         ();
    float get_F3_DATA_FP         ();
    float get_EMR_N_THRESHOLD    ();
    float get_WRN_N_THRESHOLD    ();
    float get_EMR_T_THRESHOLD    ();
    float get_WRN_T_THRESHOLD    ();
    bool  get_EMR_N              ();
    bool  get_WRN_N              ();
    bool  get_EMR_T              ();
    bool  get_WRN_T              ();
    bool  get_R1                 ();
    bool  get_R2                 ();
    bool  get_R3                 ();
    bool  get_RDY                ();
    bool  get_TEST               ();
    bool  get_XXXX               ();    
    
private:
    libModbusSystematomSPU_private* _p;

    std::string stdErrorMsg(std::string functionName, std::string errorMsg, std::string exptionMsg);
    float conv2RegsToFloat(uint16_t data1, uint16_t data2);
    float get_1_DATA_FP(int start_address);
    uint16_t get_1_DATA(int address);
};
