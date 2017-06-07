using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RuleAnalysis
{
    class RuleCondition
    {

        /// <summary>
        /// content:[!]"<content string>";
        /// </summary>
        public string Content { get; set; }

        /// <summary>
        /// Means the content is !"<Content String>"
        /// </summary>
        public bool Negative { get; set; }

        /// <summary>
        ///  protected_content:[!]"<content hash>", length:orig_len[, hash:md5|sha256|sha512];
        /// </summary>
        public string ProtectedContent { get; set; }

        /// <summary>
        /// hash:[md5|sha256|sha512];
        /// </summary>
        public string Hash { get; set; }

        /// <summary>
        ///  length:[<original_length>];
        /// </summary>
        public string Length { get; set; }

        /// <summary>
        /// nocase;
        /// </summary>
        public string Nocase { get; set; }

        /// <summary>
        /// rawbytes 
        /// </summary>
        public string Rawbytes { get; set; }

        /// <summary>
        /// depth:[<number>|<var_name>];
        /// </summary>
        public string Depth { get; set; }

        /// <summary>
        ///  offset:[<number>|<var_name>];
        /// </summary>
        public string Offset { get; set; }

        /// <summary>
        /// distance:[<byte_count>|<var_name>];
        /// </summary>
        public string Distance { get; set; }

        /// <summary>
        /// within:[<byte_count>|<var_name>];
        /// </summary>
        public string Within { get; set; }

        /// <summary>
        /// http_client_body;
        /// </summary>
        public string Http_client_body { get; set; }

        /// <summary>
        /// http_cookie;
        /// </summary>
        public string Http_cookie { get; set; }

        /// <summary>
        /// http_raw_cookie;
        /// </summary>
        public string Http_raw_cookie { get; set; }

        /// <summary>
        /// http_header;
        /// </summary>
        public string Http_header { get; set; }

        /// <summary>
        /// http_raw_header;
        /// </summary>
        public string Http_raw_header { get; set; }

        /// <summary>
        /// http_method;
        /// </summary>
        public string Http_method { get; set; }

        /// <summary>
        /// http_uri;
        /// </summary>
        public string Http_uri { get; set; }

        /// <summary>
        /// http_raw_uri;
        /// </summary>
        public string Http_raw_uri { get; set; }

        /// <summary>
        /// http_stat_code;
        /// </summary>
        public string Http_stat_code { get; set; }

        /// <summary>
        /// http_stat_msg;
        /// </summary>
        public string Http_stat_msg { get; set; }

        /// <summary>
        /// http_encode:[uri|header|cookie], [!][<utf8|double_encode|non_ascii|uencode|bare_byte|ascii|iis_encode>];
        /// </summary>
        public string Http_encode { get; set; }

        /// <summary>
        /// fast_pattern;
        /// fast_pattern:only;
        /// fast_pattern:<offset>,<length>;
        /// </summary>
        public string FastPattern { get; set; }

        /// <summary>
        /// uricontent:[!]"<content string>";
        /// </summary>
        public string Uricontent { get; set; }

        /// <summary>
        /// urilen:min<>max[,<uribuf>];
        /// urilen:[<|>]<number>[,<uribuf>];
        /// </summary>
        public string Urilen { get; set; }

        /// <summary>
        /// isdataat:[!]<int>[, relative|rawbytes];
        /// </summary>
        public string Isdataat { get; set; }

        /// <summary>
        /// pcre:[!]"(/<regex>/|m<delim><regex><delim>)[ismxAEGRUBPHMCOIDKYS]";
        /// </summary>
        public string Pcre { get; set; }

        /// <summary>
        /// pkt_data;
        /// </summary>
        public string PktData { get; set; }

        /// <summary>
        /// file_data;
        /// </summary>
        public string FileData { get; set; }

        /// <summary>
        /// base64_decode[:[bytes <bytes_to_decode>][, ][offset <offset>[, relative]]];
        /// </summary>
        public string Base64Decode { get; set; }

        /// <summary>
        /// base64_data;
        /// </summary>
        public string Base64Data { get; set; }

        /// <summary>
        /// byte_test:<bytes to convert>, [!]<operator>, <value>, <offset>  \
        /// [, relative][, <endian>][, string, <number type>][, dce];
        /// </summary>
        public string ByteTest { get; set; }

        /// <summary>
        /// byte_jump:<bytes_to_convert>, <offset>....
        /// </summary>
        public string ByteJump { get; set; }

        /// <summary>
        /// byte_extract:<bytes_to_extract>, <offset>, <name> 
        /// </summary>
        public string ByteExtract { get; set; }

        /// <summary>
        /// ftpbounce;
        /// </summary>
        public string Ftpbounce { get; set; }

        /// <summary>
        ///  asn1:[bitstring_overflow][, double_overflow][, oversize_length <value>][, absolute_offset <value>|relative_offset <value>];
        /// </summary>
        public string Asn1 { get; set; }

        /// <summary>
        /// cvs:<option>;
        /// </summary>
        public string Cvs { get; set; }

        /// <summary>
        /// dce_iface 
        /// </summary>
        public string DceIface { get; set; }

        /// <summary>
        /// dce_opnum 
        /// </summary>
        public string DceOpnum { get; set; }

        /// <summary>
        /// dce_stub_data 
        /// </summary>
        public string DceStubData { get; set; }

        /// <summary>
        /// sip_method 
        /// </summary>
        public string SipMethod { get; set; }

        /// <summary>
        /// sip_stat_code 
        /// </summary>
        public string SipStatCode { get; set; }

        /// <summary>
        /// sip_header 
        /// </summary>
        public string SipHeader { get; set; }

        /// <summary>
        /// sip_body 
        /// </summary>
        public string SipBody { get; set; }

        /// <summary>
        /// gtp_type 
        /// </summary>
        public string gtp_type { get; set; }

        /// <summary>
        ///  gtp_info 
        /// </summary>
        public string GtpInfo { get; set; }

        /// <summary>
        /// gtp_version 
        /// </summary>
        public string GtpVersion { get; set; }

        /// <summary>
        /// ssl_version 
        /// </summary>
        public string SslVersion { get; set; }

        /// <summary>
        /// ssl_state 
        /// </summary>
        public string SslState { get; set; }

    }
}
