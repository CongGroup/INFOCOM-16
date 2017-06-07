using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Text.RegularExpressions;

//This structure is for Payload Rule

namespace RuleAnalysis
{
    class SnortRule
    {

        public SnortRule()
        {
            Reference = new List<string>();
            Conditions = new List<RuleCondition>();
        }

        #region Rule Header

        /// <summary>
        /// 1.alert  2.log  3.pass  4.activate  5.dynamic  6.drop  7.reject  8.sdrop 
        /// </summary>
        public string Actions { get; set; }

        /// <summary>
        /// TCP, UDP, ICMP, and IP 
        /// </summary>
        public string Protocols { get; set; }

        /// <summary>
        /// [!] IP/24
        /// </summary>
        public string FromAddress { get; set; }

        /// <summary>
        /// [!] IP/24
        /// </summary>
        public string ToAddress { get; set; }

        /// <summary>
        /// Port
        /// </summary>
        public string FromPort { get; set; }

        /// <summary>
        /// Port
        /// </summary>
        public string ToPort { get; set; }

        /// <summary>
        /// operator -> etc.
        /// </summary>
        public string Operator { get; set; }

        /// <summary>
        /// for Activate rule
        /// </summary>
        public string Activate { get; set; }

        /// <summary>
        /// Dynamic Rules Params
        /// </summary>
        public string ActivatedBy { get; set; }

        /// <summary>
        /// Dynamic Rules Params
        /// </summary>
        public string Count { get; set; }

        /// <summary>
        /// the RawData of Conditions
        /// </summary>
        public string ConditionString { get; set; }


        #endregion

        #region General Rule Option

        /// <summary>
        /// msg:"<message text>";
        /// </summary>
        public string Msg { get; set; }

        /// <summary>
        ///  reference:<id system>, <id>; [reference:<id system>, <id>;]
        /// </summary>
        public List<string> Reference { get; set; }

        /// <summary>
        /// gid:<generator id>;
        /// </summary>
        public string Gid { get; set; }

        /// <summary>
        /// sid:<snort rules id>;
        /// </summary>
        public string Sid { get; set; }

        /// <summary>
        /// rev:<revision integer>;
        /// </summary>
        public string Rev { get; set; }

        /// <summary>
        /// classtype:<class name>;
        /// </summary>
        public string Classtype { get; set; }

        /// <summary>
        /// priority:<priority integer>;
        /// </summary>
        public string Priority { get; set; }

        /// <summary>
        /// metadata:key1 value1, key2 value2;
        /// </summary>
        public string Metadata { get; set; }

        #endregion

        #region Payload Option

        /// <summary>
        /// Conditions about the Rule
        /// </summary>
        public List<RuleCondition> Conditions { get; set; }

        #endregion

        #region Private Method

        private RuleCondition Transform(string sCon)
        {
            RuleCondition ruleCondition = new RuleCondition();

            //Content
            ruleCondition.Content = RegexHelper.MatchSingle("content:\"(.*?)\";", sCon);

            if (ruleCondition.Content == "")
            {
                ruleCondition.Content = RegexHelper.MatchSingle("content:[!]?\"(.*?)\";", sCon);
                ruleCondition.Negative = true;
            }

            //nocase
            ruleCondition.Nocase = RegexHelper.MatchCount("; nocase;", sCon) ? "1" : "0";

            //http_header
            ruleCondition.Http_header = RegexHelper.MatchCount("; http_header;", sCon) ? "1" : "0";

            //pcre
            ruleCondition.Pcre = RegexHelper.MatchSingle("pcre:\"(.*?)\";", sCon);

            //fast_pattern
            ruleCondition.FastPattern = RegexHelper.MatchCount("; fast_pattern;", sCon) ? "1" : "0";

            //within
            ruleCondition.Within = RegexHelper.MatchSingle("within:(.*?);", sCon);

            //file_data
            ruleCondition.FileData = RegexHelper.MatchCount("; file_data;", sCon) ? "1" : "0";

            //asn1
            ruleCondition.Asn1 = RegexHelper.MatchSingle("asn1:(.*?);", sCon);

            //distance
            ruleCondition.Distance = RegexHelper.MatchSingle("distance:(.*?);", sCon);

            //byte_test
            ruleCondition.ByteTest = RegexHelper.MatchSingle("byte_test:(.*?);", sCon);

            //base64_decode
            ruleCondition.Base64Decode = RegexHelper.MatchSingle("base64_decode:(.*?);", sCon);

            //base64_data
            ruleCondition.Base64Data = RegexHelper.MatchCount("; base64_data;", sCon) ? "1" : "0";

            //offset
            ruleCondition.Offset = RegexHelper.MatchSingle("offset:(.*?);", sCon);

            //depth
            ruleCondition.Depth = RegexHelper.MatchSingle("depth:(.*?);", sCon);

            //http_client_body
            ruleCondition.Http_client_body = RegexHelper.MatchCount("; http_client_body;", sCon) ? "1" : "0";

            //http_cookie
            ruleCondition.Http_cookie = RegexHelper.MatchCount("; http_cookie;", sCon) ? "1" : "0";

            //http_uri
            ruleCondition.Http_uri = RegexHelper.MatchCount("; http_uri;", sCon) ? "1" : "0";

            //http_stat_code
            ruleCondition.Http_stat_code = RegexHelper.MatchCount("; http_stat_code;", sCon) ? "1" : "0";

            //http_raw_uri
            ruleCondition.Http_raw_uri = RegexHelper.MatchCount("; http_raw_uri;", sCon) ? "1" : "0";

            //http_method
            ruleCondition.Http_method = RegexHelper.MatchCount("; http_method;", sCon) ? "1" : "0";

            //urilen
            ruleCondition.Urilen = RegexHelper.MatchSingle("urilen:(.*?);", sCon);

            //ssl_state
            ruleCondition.SslState = RegexHelper.MatchSingle("ssl_state:(.*?);", sCon);

            //isdataat
            ruleCondition.Isdataat = RegexHelper.MatchSingle("isdataat:(.*?);", sCon);

            //pkt_data;
            ruleCondition.PktData = RegexHelper.MatchCount("; pkt_data;", sCon) ? "1" : "0";

            return ruleCondition;
        }

        #endregion


        #region Public Init Method

        public void InitCondition()
        {

            #region General Rule Attribute

            //Msg
            Msg = RegexHelper.MatchSingle("msg:\"(.*?)\"", ConditionString);

            //Reference
            Reference = RegexHelper.MatchMulti("reference:(.*?);", ConditionString);

            //sid
            Sid = RegexHelper.MatchSingle("sid:(.*?);", ConditionString);

            //rev
            Rev = RegexHelper.MatchSingle("rev:(.*?);", ConditionString);

            //classtype
            Classtype = RegexHelper.MatchSingle("classtype:(.*?);", ConditionString);

            //Metadata
            Metadata = RegexHelper.MatchSingle("metadata:(.*?);", ConditionString);

            #endregion


            #region Multi Conditions

            string sAllContent = RegexHelper.MatchSingle("(content:[!]?.*)", ConditionString);

            List<string> listCons = new List<string>();

            //Get All 
            string sConditionString = sAllContent;
            while (true)
            {

                string sCon = RegexHelper.MatchSingle("^(content:[!]?\".*?)content:[!]?\"", sConditionString);
                if (sCon == "")
                {
                    break;
                }
                listCons.Add(sCon);
                sConditionString = sConditionString.Replace(sCon, "");

            }
            if (sConditionString.IndexOf("content:") >= 0)
            {
                listCons.Add(sConditionString);
            }

            foreach (string sCon in listCons)
            {
                RuleCondition ruleCondition = Transform(sCon);
                Conditions.Add(ruleCondition);
            }

            #endregion



        }

        #endregion

    }
}
