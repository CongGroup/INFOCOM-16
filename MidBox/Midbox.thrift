/***********************************************************
 * Vss Thrift Script
 * Made By XinyuWang
 * 2015/6/1
 ***********************************************************/

namespace java mb
namespace cpp mb
namespace rb mb
namespace py mb
namespace perl mb
namespace csharp mb

//"required" and "optional" keywords are purely for documentation.

struct TQueryKey {
  1: required string Trapdoor,
  2: required string Mask
}

service TMidboxService {

  /**
   * Send the QueryKey to Midbox.
   */
  void Query(
    1: required list<TQueryKey> trapdoors
  );

  /**
   * Send the Http Payload to Midbox.
   */
  void WebRequest(
    1: required string sPayload
  );

  
}
