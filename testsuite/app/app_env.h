/******************************************************************************
   Copyright 2020 Embedded Office GmbH & Co. KG

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************/

#ifndef _APP_ENV_H_
#define _APP_ENV_H_

/******************************************************************************
* INCLUDES
******************************************************************************/

#include "app.h"
#include "app_emcy.h"
#include "app_dict.h"
#include "app_dom.h"
#include "app_hooks.h"
#include "app_stdobj.h"
#include "ts_env.h"
#include "drv_can.h"

/******************************************************************************
* PUBLIC MACROS
******************************************************************************/

#define BYTE(f,p)            (uint8_t)((f).Data[(p)])

#define WORD(f,p)            ((uint16_t)((f).Data[(p)+1]) << 8 | \
                              (uint16_t)((f).Data[(p)]))

#define LONG(f,p)            ((uint32_t)((f).Data[(p)+3]) << 24 | \
                              (uint32_t)((f).Data[(p)+2]) << 16 | \
                              (uint32_t)((f).Data[(p)+1]) << 8  | \
                              (uint32_t)((f).Data[(p)]))

#define TS_SYNC_SEND()       SetRxFrm(0, 10, 0x080, 0,  \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0));       \
                             RunSimCan(0, 0)

#define TS_NMT_SEND(c,n)     SetRxFrm(0, 0, 0x000, 2,  \
                               (uint8_t)(c),        \
                               (uint8_t)(n),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0));       \
                             RunSimCan(0, 0)

#define TS_SDO_SEND(c,i,s,d) SetRxFrm(0, 0, 0x601, 8,              \
                               (uint8_t)(c),                    \
                               (uint8_t)(i),                    \
                               (uint8_t)(((uint16_t)i)>>8),   \
                               (uint8_t)(s),                    \
                               (uint8_t)(d),                    \
                               (uint8_t)(((uint32_t)d)>>8),   \
                               (uint8_t)(((uint32_t)d)>>16),  \
                               (uint8_t)(((uint32_t)d)>>24)); \
                             RunSimCan(0, 0)

#define TS_EBLK_SEND(c,d)    SetRxFrm(0, 0, 0x601, 8,              \
                               (uint8_t)(c),                    \
                               (uint8_t)(d),                    \
                               (uint8_t)(((uint32_t)d)>>8),   \
                               (uint8_t)(((uint32_t)d)>>16),  \
                               (uint8_t)(((uint32_t)d)>>24),  \
                               (uint8_t)(0),                    \
                               (uint8_t)(0),                    \
                               (uint8_t)(0));                   \
                             RunSimCan(0, 0)

#define TS_ACKBLK_SEND(c,a,s) SetRxFrm(0, 0, 0x601, 8, \
                               (uint8_t)(c),        \
                               (uint8_t)(a),        \
                               (uint8_t)(s),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0));       \
                             RunSimCan(0, 0)

#define TS_SEG_SEND(s,a)     SetRxFrm(0, 0, 0x601, 8,  \
                               (uint8_t)(s),        \
                               (uint8_t)(a+0),      \
                               (uint8_t)(a+1),      \
                               (uint8_t)(a+2),      \
                               (uint8_t)(a+3),      \
                               (uint8_t)(a+4),      \
                               (uint8_t)(a+5),      \
                               (uint8_t)(a+6));     \
                             RunSimCan(0, 0)

#define TS_HB_SEND(n,s)      SetRxFrm(0, 0, 1792+n, 1, \
                               (uint8_t)(s),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0),        \
                               (uint8_t)(0));       \
                             RunSimCan(0, 0)

#define TS_PDO_SEND(i,a)    SetRxFrm(0, 0, (i), 8,   \
                               (uint8_t)((a)+0),  \
                               (uint8_t)((a)+1),  \
                               (uint8_t)((a)+2),  \
                               (uint8_t)((a)+3),  \
                               (uint8_t)((a)+4),  \
                               (uint8_t)((a)+5),  \
                               (uint8_t)((a)+6),  \
                               (uint8_t)((a)+7)); \
                            RunSimCan(0, 0)

#define TS_LSS_SEND(c,d1,d2) SetRxFrm(0, 0, 2021, 8,\
                               (uint8_t)(c),   \
                               (uint8_t)(d1),  \
                               (uint8_t)(d2),  \
                               (uint8_t)(0),   \
                               (uint8_t)(0),   \
                               (uint8_t)(0),   \
                               (uint8_t)(0),   \
                               (uint8_t)(0));  \
                             RunSimCan(0, 0)

#define TS_LSS_SEND_W(c,d) SetRxFrm(0, 0, 2021, 8,                 \
                               (uint8_t)(c),                    \
                               (uint8_t)(d),                    \
                               (uint8_t)(((uint16_t)d)>>8),   \
                               (uint8_t)(0),                    \
                               (uint8_t)(0),                    \
                               (uint8_t)(0),                    \
                               (uint8_t)(0),                    \
                               (uint8_t)(0));                   \
                             RunSimCan(0, 0)

#define TS_LSS_SEND_L(c,d) SetRxFrm(0, 0, 2021, 8,                 \
                               (uint8_t)(c),                    \
                               (uint8_t)(d),                    \
                               (uint8_t)(((uint32_t)d)>>8),   \
                               (uint8_t)(((uint32_t)d)>>16),  \
                               (uint8_t)(((uint32_t)d)>>24),  \
                               (uint8_t)(0),                    \
                               (uint8_t)(0),                    \
                               (uint8_t)(0));                   \
                             RunSimCan(0, 0)

#define CHK_NO_ERR(n)        TS_ASSERT(CO_ERR_NONE == CONodeGetErr(n))

#define CHK_ERR(n,e)         TS_ASSERT(e == CONodeGetErr(n))

#define CHK_CAN(f)           TS_ASSERT(1 == GetFrm(0,(uint8_t*)(f),sizeof(CO_IF_FRM)))

#define CHK_NOCAN(f)         TS_ASSERT(0 == GetFrm(0,(uint8_t*)(f),sizeof(CO_IF_FRM)))

#define CHK_BOOTUP(f,n)      TS_ASSERT((1792+(n)) == (f).Identifier); \
                             TS_ASSERT(1          == (f).DLC);        \
                             TS_ASSERT(0          == BYTE((f),0))

#define CHK_NMT(f,n,s)       TS_ASSERT((1792+(n)) == (f).Identifier); \
                             TS_ASSERT(1          == (f).DLC);        \
                             TS_ASSERT((s)        == BYTE((f),0))

#define CHK_MODE(n,m)        TS_ASSERT((m) == CONmtGetMode(n))

#define CHK_SDO0(f,c)        TS_ASSERT(0x581 == (f).Identifier); \
                             TS_ASSERT(8     == (f).DLC);        \
                             TS_ASSERT((c)   == BYTE((f),0))

#define CHK_SDO0_OK(i,s)     { CO_IF_FRM f;                                                      \
                               TS_ASSERT(1     == GetFrm(0,(uint8_t*)(&f),sizeof(CO_IF_FRM)));\
                               TS_ASSERT(0x581 == (f).Identifier);                                    \
                               TS_ASSERT(8     == (f).DLC);                                           \
                               TS_ASSERT(0x60  == BYTE(f,0));                                         \
                               TS_ASSERT((i)   == WORD(f,1));                                         \
                               TS_ASSERT((s)   == BYTE(f,3));                                         \
                               TS_ASSERT(0     == LONG(f,4));                                         \
                             }


#define CHK_SDO0_ERR(i,s,e)  { CO_IF_FRM f;                                                      \
                               TS_ASSERT(1     == GetFrm(0,(uint8_t*)(&f),sizeof(CO_IF_FRM)));\
                               TS_ASSERT(0x581 == (f).Identifier);                                    \
                               TS_ASSERT(8     == (f).DLC);                                           \
                               TS_ASSERT(0x80  == BYTE(f,0));                                         \
                               TS_ASSERT((i)   == WORD(f,1));                                         \
                               TS_ASSERT((s)   == BYTE(f,3));                                         \
                               TS_ASSERT((e)   == LONG(f,4));                                         \
                             }

#define CHK_PDO0(f,i,d)      TS_ASSERT((i) == (f).Identifier); \
                             TS_ASSERT((d) == (f).DLC)

#define CHK_EMCY(f)          { uint32_t id;                                  \
                               CODictRdLong(&node.Dict, CO_DEV(0x1014,0), &id);  \
                               TS_ASSERT(id == (f).Identifier);                \
                               TS_ASSERT(8  == (f).DLC);                       \
                             }

#define CHK_LSS_OK(c)        { CO_IF_FRM f;                                                     \
                               TS_ASSERT(1    == GetFrm(0,(uint8_t*)(&f),sizeof(CO_IF_FRM)));\
                               TS_ASSERT(2020 == (f).Identifier);                                    \
                               TS_ASSERT(8    == (f).DLC);                                           \
                               TS_ASSERT((c)  == BYTE(f,0));                                         \
                               TS_ASSERT(0    == WORD(f,1));                                         \
                               TS_ASSERT(0    == BYTE(f,3));                                         \
                               TS_ASSERT(0    == LONG(f,4));                                         \
                             }

#define CHK_BYTE(f,p,v)      TS_ASSERT((uint8_t)(v & 0xFF) == BYTE((f),(p)))

#define CHK_WORD(f,p,v)      TS_ASSERT((uint16_t)(v) == WORD((f),(p)))

#define CHK_LONG(f,p,v)      TS_ASSERT((uint32_t)(v) == LONG((f),(p)))

#define CHK_MLTPX(f,i,s)     TS_ASSERT((i) == WORD(f,1)); \
                             TS_ASSERT((s) == BYTE(f,3))

#define CHK_DATA(f,d)        TS_ASSERT((d) == LONG(f,4))

#define CHK_ACKSEQ(f,s)      TS_ASSERT((s) == BYTE(f,1))

#define CHK_NEXTBLK(f,s)     TS_ASSERT((s) == BYTE(f,2)); \
                             TS_ASSERT(0   == BYTE(f,3)); \
                             TS_ASSERT(0   == LONG(f,4))


#define CHK_BLKSIZE(f,s)     TS_ASSERT((s) == BYTE(f,4)); \
                             TS_ASSERT(0   == BYTE(f,5)); \
                             TS_ASSERT(0   == BYTE(f,6)); \
                             TS_ASSERT(0   == BYTE(f,7))

#define SET_OBJ08(i,s,v)     { int16_t num;                                   \
                               num = CODictWrByte(&node.Dict,CO_DEV((i),(s)),(v)); \
                               TS_ASSERT(CO_ERR_NONE == num);                    \
                             }

#define CHK_OBJ08(i,s,v)     { uint8_t para;                                    \
                               int16_t num;                                     \
                               num = CODictRdByte(&node.Dict,CO_DEV((i),(s)),&para); \
                               TS_ASSERT(CO_ERR_NONE == num);                      \
                               TS_ASSERT((v)         == para);                     \
                             }

#define SET_OBJ16(i,s,v)     { int16_t num;                                    \
                               num = CODictWrWord(&node.Dict,CO_DEV((i),(s)),(v));  \
                               TS_ASSERT(CO_ERR_NONE == num);                     \
                             }

#define CHK_OBJ16(i,s,v)     { uint16_t para;                                    \
                               int16_t num;                                     \
                               num = CODictRdWord(&node.Dict,CO_DEV((i),(s)),&para); \
                               TS_ASSERT(CO_ERR_NONE == num);                      \
                               TS_ASSERT((v)         == para);                     \
                             }

#define SET_OBJ32(i,s,v)     { int16_t num;                                   \
                               num = CODictWrLong(&node.Dict,CO_DEV((i),(s)),(v)); \
                               TS_ASSERT(CO_ERR_NONE == num);                    \
                             }

#define CHK_OBJ32(i,s,v)     { uint32_t para;                                    \
                               int16_t num;                                     \
                               num = CODictRdLong(&node.Dict,CO_DEV((i),(s)),&para); \
                               TS_ASSERT(CO_ERR_NONE == num);                      \
                               TS_ASSERT((v)         == para);                     \
                             }

#define CHK_ZERO(f)          TS_ASSERT(0 == WORD(f,1)); \
                             TS_ASSERT(0 == BYTE(f,3)); \
                             TS_ASSERT(0 == LONG(f,4))

#define CHK_SEG(f,a,n)       TS_ASSERT(((uint8_t)(a) & 0xFF) == BYTE(f,1));          \
                             if (n > 1) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 1) & 0xFF) == BYTE(f, 2)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 2));                            \
                             }                                                          \
                             if (n > 2) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 2) & 0xFF) == BYTE(f, 3)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 3));                            \
                             }                                                          \
                             if (n > 3) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 3) & 0xFF) == BYTE(f, 4)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 4));                            \
                             }                                                          \
                             if (n > 4) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 4) & 0xFF) == BYTE(f, 5)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 5));                            \
                             }                                                          \
                             if (n > 5) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 5) & 0xFF) == BYTE(f, 6)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 6));                            \
                             }                                                          \
                             if (n > 6) {                                               \
                                 TS_ASSERT(((uint8_t)(a + 6) & 0xFF) == BYTE(f, 7)); \
                             } else {                                                   \
                                 TS_ASSERT(0 == BYTE(f, 7));                            \
                             }

#define CHK_DOM_FULL(d,s)    TS_ASSERT(0 == TS_DomainCheck((d),(s),0))

#define CHK_DOM_PART(d,s,m)  TS_ASSERT(0 == TS_DomainCheck((d),(s),(uint8_t)(m)))

#define CHK_TMR_CALL(n)      TS_ASSERT((n) == TS_TmrCallCnt)

#define SET_TMR_CNT(n)       TS_TmrCallCnt = (uint32_t)(n)

#define TEST_DEF(name)       TS_DEF_MAIN(name)

/******************************************************************************
* PUBLIC VARIABLES
******************************************************************************/

extern uint32_t  TS_TmrCallCnt;

/******************************************************************************
* PUBLIC FUNCTIONS
******************************************************************************/

/*---------------------------------------------------------------------------*/
/*! \brief CAN INTERRUPT HANDLER
*
* \details Connect the CAN communication with the CANopen node for testing.
*/
/*---------------------------------------------------------------------------*/
void TS_CanIsr(void);

/*---------------------------------------------------------------------------*/
/*! \brief CANOPEN NODE SPECIFICATION
*
* \details Create the CANopen node specification for testing.
*
* \param   node
*          CANopen node for testing
*
* \param   spec
*          Specification for CANopen node for testing
*/
/*---------------------------------------------------------------------------*/
void TS_CreateSpec(CO_NODE *node, CO_NODE_SPEC *spec);

/*---------------------------------------------------------------------------*/
/*! \brief CREATE CANOPEN NODE
*
* \details Create the CANopen node instance for testing.
*
* \param   node
*          CANopen node for testing
*/
/*---------------------------------------------------------------------------*/
void TS_CreateNode(CO_NODE *node);

/*---------------------------------------------------------------------------*/
/*! \brief CREATE AND START CANOPEN NODE
*
* \details Create the CANopen node instance for testing and start the
*          operational mode for this node.
*
* \param   node
*          CANopen node for testing
*/
/*---------------------------------------------------------------------------*/
void TS_CreateNodeAutoStart(CO_NODE *node);

/*---------------------------------------------------------------------------*/
/*! \brief ADD OBJECT ENTRY INTO OBJECT DICTIONARY FOR TESTING
*
* \details Append an object entry into the dynamic object dictionary of the
*          CANopen node for testing.
*
* \param   key
*          object entry key, generated with CO_KEY()
*
* \param   type
*          object type reference according to user manual
*
* \param   data
*          object entry data according to user manual
*/
/*---------------------------------------------------------------------------*/
void TS_ODAdd(uint32_t key, const CO_OBJ_TYPE *type, uintptr_t data);

/*---------------------------------------------------------------------------*/
/*! \brief SETUP THE MANDATORY OBJECT ENTRIES OF AN OBJECT DICTIONARY
*
* \details Append the mandatory object entries into an empty object
*          dictionary for use in the CANopen node for testing.
*/
/*---------------------------------------------------------------------------*/
void TS_CreateMandatoryDir(void);

/*---------------------------------------------------------------------------*/
/*! \brief ADD RPDO #N COMMUNICATION SETTINGS TO OBJECT DICTIONARY
*
* \details Append the object entries for RPDO communication settings.
*
* \param   num
*          Number of RPDO (0..511)
*
* \param   id
*          Reference to COB-ID for RPDO
*
* \param   type
*          Reference to RPDO type variable
*/
/*---------------------------------------------------------------------------*/
void TS_CreateRPdoCom(uint8_t num, uint32_t *id, uint8_t *type);

/*---------------------------------------------------------------------------*/
/*! \brief ADD RPDO #N APPLICATION OBJECT MAPPINGS
*
* \details Append the object entries for RPDO mapping settings.
*
* \param   num
*          Number of RPDO (0..511)
*
* \param   map
*          Reference to array of maximal possible mapping entries
*
* \param   len
*          Reference to variable with length of array
*/
/*---------------------------------------------------------------------------*/
void TS_CreateRPdoMap(uint8_t num, uint32_t *map, uint8_t *len);

/*---------------------------------------------------------------------------*/
/*! \brief ADD TPDO #N COMMUNICATION SETTINGS TO OBJECT DICTIONARY
*
* \details Append the object entries for TPDO communication settings.
*
* \param   num
*          Number of TPDO (0..511)
*
* \param   id
*          Reference to COB-ID for TPDO
*
* \param   type
*          Reference to TPDO type variable
*
* \param   inhibit
*          Reference to inhibit time (in 100us)
*
* \param   evtimer
*          Reference to event timer (in 1ms)
*/
/*---------------------------------------------------------------------------*/
void TS_CreateTPdoCom(uint8_t   num,
                      uint32_t *id,
                      uint8_t  *type,
                      uint16_t *inhibit,
                      uint16_t *evtimer);

/*---------------------------------------------------------------------------*/
/*! \brief ADD TPDO #N APPLICATION OBJECT MAPPINGS
*
* \details Append the object entries for TPDO mapping settings.
*
* \param   num
*          Number of TPDO (0..511)
*
* \param   map
*          Reference to array of maximal possible mapping entries
*
* \param   len
*          Reference to variable with length of array
*/
/*---------------------------------------------------------------------------*/
void TS_CreateTPdoMap(uint8_t num, uint32_t *map, uint8_t *len);

/*---------------------------------------------------------------------------*/
/*! \brief SIMULATE TIME
*
* \details Wait for the given amount of milliseconds
*
* \param   node
*          Reference to the CANopen testing node
*
* \param   millisec
*          Number of milliseconds the function shall wait
*/
/*---------------------------------------------------------------------------*/
void TS_Wait(CO_NODE *node, uint32_t millisec);

/*---------------------------------------------------------------------------*/
/*! \brief DEFAULT TIMER TEST CALLBACK
*
* \details This default callback function counts internally, how often the
*          callback is activated. The checking macros CHK_TMR_CALL(n) will
*          check for a given amount of calls and SET_TMR_CNT(n) will (re)set
*          the internal counter value.
*
* \param   arg
*          Reference to callback arguments (unused)
*/
/*---------------------------------------------------------------------------*/
void TS_TmrFunc(void *arg);

/*---------------------------------------------------------------------------*/
/*! \brief CHECK THE DOMAIN CONTENT
*
* \details This function checks the expected content of a domain. The
*          expected content is given as start value and a missing limit.
*          We expect, that the content up to the missing limit holds the
*          value 0xff. After the missing value, the upcounting byte value
*          is expected.
*
* \param   dom
*          Reference to domain management structure
*
* \param   start
*          Start value of the upcounting byte values
*
* \param   missing
*          Limit value for missing values
*/
/*---------------------------------------------------------------------------*/
int16_t TS_DomainCheck(CO_OBJ_DOM *dom, uint8_t start, uint8_t missing);

/*---------------------------------------------------------------------------*/
/*! \brief SEND A BLOCK WITH SDO SEGMENTED TRANSFER
*
* \details This function simulates the procedure when a SDO segmented
*          transfer is initiated by a SDO client.
*
* \param   start
*          Start value of the upcounting byte counter
*
* \param   segnum
*          Number of segments we want to send
*
* \param   last
*          Set to 1 if this is the last segment
*
* \param   seglost
*          Set to value >0 when sending shall skip the segment seglost
*/
/*---------------------------------------------------------------------------*/
void TS_SendBlk(uint32_t start, uint8_t segnum, uint8_t last, uint8_t seglost);

#endif
