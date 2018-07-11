/*
 * This file is a sample program.
 * Written by M.Yasaka on 6/17/2018
 *
 * handler.c
 * Handling the basic operation for the bdb.
 */

#include <glib-object.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include <thrift/c_glib/thrift.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol_factory.h>
#include <thrift/c_glib/protocol/thrift_protocol_factory.h>
#include <thrift/c_glib/server/thrift_server.h>
#include <thrift/c_glib/server/thrift_simple_server.h>
#include <thrift/c_glib/transport/thrift_buffered_transport_factory.h>
#include <thrift/c_glib/transport/thrift_server_socket.h>
#include <thrift/c_glib/transport/thrift_server_transport.h>

#include "gen-c_glib/thbdb_basic.h"
#include "gen-c_glib/thbdb_thbdb_types.h"
#include "handler.h"

/* ---------------------------------------------------------------- */

/* The implementation of ThbdbBasicimplHandler follows. */

G_DEFINE_TYPE (ThbdbBasicimplHandler,
               thbdb_basicimpl_handler,
               THBDB_TYPE_BASIC_HANDLER)

/* Each of a handler's methods accepts at least two parameters: A
   pointer to the service-interface implementation (the handler object
   itself) and a handle to a GError structure to receive information
   about any error that occurs.

   On success, a handler method returns TRUE. A return value of FALSE
   indicates an error occurred and the error parameter has been
   set. (Methods should not return FALSE without first setting the
   error parameter.) */

static gboolean
thbdb_basicimpl_handler_hello(thbdbBasicIf * iface, gchar ** _return, const gchar * arg, GError ** error)
{
  THRIFT_UNUSED_VAR (iface);
  THRIFT_UNUSED_VAR (error);

  //@@@

  puts (" ^^ hello() ^^");
   
  GString *retValue;
  retValue = g_string_new( "" );
  g_string_printf( retValue ,"Server received: %s \n" , arg );
  puts( retValue->str );
  
  *_return = retValue->str;
  
  return TRUE;
}


static gboolean
thbdb_basicimpl_handler_put (thbdbBasicIf * iface, const gchar * key, const gchar * value, thbdbInvalidOperation ** exp, GError ** error)
{

  //@@@
  puts (" ^^ put() ^^");

  g_return_val_if_fail (THBDB_IS_BASIC_HANDLER (iface), FALSE);

  return TRUE;
}




/* THBDB basicimpl Handler's instance finalizer (destructor) */
static void
thbdb_basicimpl_handler_finalize (GObject *object)
{
  ThbdbBasicimplHandler *self =
    THBDB_BASICIMPL_HANDLER (object);

  /* Free our calculation-log hash table */
  g_hash_table_unref (self->log);
  self->log = NULL;

  /* Chain up to the parent class */
  G_OBJECT_CLASS (thbdb_basicimpl_handler_parent_class)->
    finalize (object);
}

/* ThbdbBasicimplHandler's instance initializer (constructor) */
static void
thbdb_basicimpl_handler_init (ThbdbBasicimplHandler *self)
{
  //@@@
    /* Create our calculation-log hash table */
  self->log = g_hash_table_new_full (g_int_hash,
                                     g_int_equal,
                                     g_free,
                                     g_object_unref);
}

/* ThbdbBasicimplHandler's class initializer */
static void
thbdb_basicimpl_handler_class_init (ThbdbBasicimplHandlerClass *klass)
{
  //@@@
  printf( "class init ¥n " );
  
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  thbdbBasicHandlerClass *thbdb_basic_handler_class =
    THBDB_BASIC_HANDLER_CLASS (klass);

  /* Register our destructor */
  gobject_class->finalize = thbdb_basicimpl_handler_finalize;

  /* Register our implementations of CalculatorHandler's methods */
  thbdb_basic_handler_class->hello =
    thbdb_basicimpl_handler_hello;
  thbdb_basic_handler_class->put =
    thbdb_basicimpl_handler_put;
}


/* That ends the implementation of ThbdbBasicimplHandler.
   Everything below is fairly generic code that sets up a minimal
   Thrift server for Thbdb clients. */



