using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RuleAnalysis
{
    class RulesInfo
    {

        public static void Clear()
        {

            RuleNum = 0;
            TcpRuleNum = 0;
            CommonContentNum = 0;
            OffsetDepthNum = 0;
            HttpAttrNum = 0;
            RulePairs = new List<SnortPair>();
        }

        /// <summary>
        /// Snort Pairs
        /// </summary>
        public static List<SnortPair> RulePairs { get; set; }

        /// <summary>
        /// All the Rule Num
        /// </summary>
        public static int RuleNum { get; set; }

        /// <summary>
        /// All the TCP Rule Num
        /// </summary>
        public static int TcpRuleNum { get; set; }


        /// <summary>
        /// Common Content Condition
        /// e.g. content:"(.*?)" without any http_body or within, depth ...
        /// </summary>
        public static int CommonContentNum { get; set; }

        /// <summary>
        /// Condition with offset or depth
        /// </summary>
        public static int OffsetDepthNum { get; set; }


        /// <summary>
        /// Condition with Http Attribute ...
        /// </summary>
        public static int HttpAttrNum { get; set; }

        /// <summary>
        /// All the condition pair
        /// include CommonContentNum + OffsetDepthNum + HttpAttrNum
        /// </summary>
        public static int AllPairNum
        {
            get
            {
                return CommonContentNum + OffsetDepthNum + HttpAttrNum;
            }
        }

    }
}
