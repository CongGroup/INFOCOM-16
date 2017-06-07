using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RuleAnalysis
{
    class SnortPair
    {

        /// <summary>
        /// Snort Pair
        /// </summary>
        public string Key { get; set; }

        /// <summary>
        /// Snort Action
        /// </summary>
        public int Action { get; set; }

        /// <summary>
        /// Snort ID
        /// </summary>
        public string RuleID { get; set; }

        /// <summary>
        /// Offset Begin
        /// </summary>
        public int Offset { get; set; }

        /// <summary>
        /// Offset Count
        /// </summary>
        public int OffsetCount { get; set; }

        /// <summary>
        /// HTTP_Field
        /// </summary>
        public int Field { get; set; }

        /// <summary>
        /// # of Conditions
        /// </summary>
        public int ConditionNum { get; set; }

        public static int GetActionByName(string sAction)
        {
            if (sAction == "alert") { return 1; }
            if (sAction == "log") { return 2; }
            if (sAction == "pass") { return 3; }
            if (sAction == "activate") { return 4; }
            if (sAction == "dynamic") { return 5; }
            if (sAction == "drop") { return 6; }
            if (sAction == "reject") { return 7; }
            if (sAction == "sdrop") { return 8; }

            return 0;
        }

        public static int GetFieldByName(string sField)
        {
            if (sField == "http_client_body") { return 1; }

            if (sField == "http_cookie") { return 2; }
            if (sField == "http_encode") { return 3; }
            if (sField == "http_header") { return 4; }
            if (sField == "http_method") { return 5; }
            if (sField == "http_raw_cookie") { return 6; }
            if (sField == "http_raw_header") { return 7; }
            if (sField == "http_raw_uri") { return 8; }
            if (sField == "http_stat_code") { return 9; }
            if (sField == "http_stat_msg") { return 10; }
            if (sField == "http_uri") { return 11; }

            return 0;
        }
    }
}
