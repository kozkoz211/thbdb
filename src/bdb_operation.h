/*
 * This file is a sample program.
 * Written by M.Yasaka on 6/17/2018
 *
 * bdb_operation.h
 * This file contains the bdb's initializing and finalizing operations for the bdb.
 */
#ifndef BDB_OPERATION_H
#define BDB_OPERATION_H
 
#include "gen-c_glib/thbdb_thbdb_types.h"

#include <db.h>

/* for glib gerror */
GQuark
g_thbdb_error_quark (void);

/** for glib error proc */
#define G_THBDB_ERROR g_thbdb_error_quark() 

/** Following : Basic struct **/

typedef struct _bdbkeyList bdbKeyList;
struct _bdbkeyList{
    char* key;
    int size;
    struct bdbKeyList* next;
} ;

/** Following : Basic operations **/

u_int32_t put_on_bdb( char* key, int key_len, char* value, int value_len);

u_int32_t get_from_bdb( char* key,int key_len , char** value );

u_int32_t remove_from_bdb( char* key,int key_len );

u_int32_t exists_on_bdb( char* key,int key_len , int* status );

u_int32_t is_null_bdb( int* status );

// u_int32_t get_keys_from_bdb( const int position, const int size, thbdbKeys* _return );

u_int32_t compact_bdb();

u_int32_t get_keys_from_bdb( const int position, const int size, bdbKeyList* _return, int* numOfbdbKeyList );

bdbKeyList* add_bdbkey_list( DBT* src, bdbKeyList* current_lst);

/** Following : Control operations **/

u_int32_t init_bdb();

u_int32_t close_bdb();

u_int32_t unlink_bdb();

#define PROGRAM_NAME   "ThBDB"       /* The programe name used for error messages and ...  */
#define BDB_FILENAME   "thbdb.db"    /* Default database filename */
#define BDB_PAGESIZE   1024          /* A database page size of 1024 bytes. It could be at most 64KB.*/
#define BDB_CACHESIZE_GB   0         /* A database cache size (GBs) in a single region. */
#define BDB_CACHESIZE_BYTE 32*1024   /* A database cache size (Bytes) in a single region. */

#endif /* BDB_OPERATION_H */
