using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace RuleAnalysis
{
    class BLL
    {

        private static string PreProcess(string sCons)
        {
            Regex reg = new Regex("; (uricontent:\".*?\";)", RegexOptions.Singleline);
            MatchCollection mc = reg.Matches(sCons);
            foreach (Match m in mc)
            {
                if (m.Groups[1].Success)
                {
                    sCons = sCons.Replace(m.Groups[1].Value, m.Groups[1].Value.Substring(3) + " http_uri;");
                }
            }
            return sCons;

        }

        public static List<SnortRule> Transform(string sRule)
        {

            List<SnortRule> listRules = new List<SnortRule>();

            //action protocol address1 port1 op address2 port2 DetailRule
            Regex regHeader = new Regex(@"^(.*?) (.*?) (.*?) (.*?) (.*?) (.*?) (.*?) \((.*)\)$", RegexOptions.Multiline);
            MatchCollection mc = regHeader.Matches(sRule);

            RulesInfo.Clear();

            foreach (Match m in mc)
            {
                SnortRule snortRule = new SnortRule();

                snortRule.Actions = m.Groups[1].Value;
                snortRule.Protocols = m.Groups[2].Value;
                snortRule.FromAddress = m.Groups[3].Value;
                snortRule.FromPort = m.Groups[4].Value;
                snortRule.Operator = m.Groups[5].Value;
                snortRule.ToAddress = m.Groups[6].Value;
                snortRule.ToPort = m.Groups[7].Value;
                snortRule.ConditionString = PreProcess(m.Groups[8].Value);

                snortRule.InitCondition();

                #region Collect the Information of Rules

                RulesInfo.RuleNum++;

                if (snortRule.Protocols.ToLower() == "tcp")
                {
                    RulesInfo.TcpRuleNum++;
                }
                else
                {
                    continue;
                }

                foreach (RuleCondition con in snortRule.Conditions)
                {
                    //Count Http Field Condition
                    if (con.Http_client_body == "1" || con.Http_cookie == "1" || con.Http_encode == "1" || con.Http_header == "1" || con.Http_method == "1" || con.Http_raw_cookie == "1" || con.Http_raw_header == "1" || con.Http_raw_uri == "1" || con.Http_stat_code == "1" || con.Http_stat_msg == "1" || con.Http_uri == "1")
                    {
                        RulesInfo.HttpAttrNum++;

                        string sField = "";
                        if (con.Http_client_body == "1") { sField = "http_client_body"; }
                        if (con.Http_cookie == "1") { sField = "http_cookie"; }
                        if (con.Http_encode == "1") { sField = "http_encode"; }
                        if (con.Http_header == "1") { sField = "http_header"; }
                        if (con.Http_method == "1") { sField = "http_method"; }
                        if (con.Http_raw_cookie == "1") { sField = "http_raw_cookie"; }
                        if (con.Http_raw_header == "1") { sField = "http_raw_header"; }
                        if (con.Http_raw_uri == "1") { sField = "http_raw_uri"; }
                        if (con.Http_stat_code == "1") { sField = "http_stat_code"; }
                        if (con.Http_stat_msg == "1") { sField = "http_stat_msg"; }
                        if (con.Http_uri == "1") { sField = "http_uri"; }


                        RulesInfo.RulePairs.Add(new SnortPair()
                        {
                            Action = SnortPair.GetActionByName(snortRule.Actions),
                            Key = con.Content,
                            RuleID = snortRule.Sid,
                            Field = SnortPair.GetFieldByName(sField),
                            Offset = -1,
                            OffsetCount = 0,
                            ConditionNum = snortRule.Conditions.Count
                        });

                        continue;
                    }

                    //Count Offset Depth Condition
                    if (con.Depth != "" && con.Offset == "")
                    {
                        con.Offset = "0";
                    }

                    if (con.Offset != "")
                    {
                        //Check the depth
                        if (con.Depth == "")
                        {
                            RulesInfo.OffsetDepthNum++;

                            RulesInfo.RulePairs.Add(new SnortPair()
                            {
                                Action = SnortPair.GetActionByName(snortRule.Actions),
                                Key = con.Content,
                                RuleID = snortRule.Sid,
                                Field = -1,
                                Offset = Int32.Parse(con.Offset),
                                OffsetCount = 1,
                                ConditionNum = snortRule.Conditions.Count
                            });

                            continue;
                        }
                        else
                        {
                            int iDepth = Int32.Parse(con.Depth);
                            List<string> arBinary = RegexHelper.MatchMulti(@"\|(.*?)\|", con.Content);
                            int iLen = con.Content.Length;
                            foreach (string sBinary in arBinary)
                            {
                                //|00 01 02| = 3 bytes  
                                iLen += (sBinary.Length + 1) / 3;
                                //sBinary.Length + 2 x || 's Length
                                iLen -= (sBinary.Length + 2);
                            }

                            if (iDepth < iLen)
                            {
                                //Begin an Error
                            }
                            RulesInfo.OffsetDepthNum += (iDepth - iLen + 1);

                            RulesInfo.RulePairs.Add(new SnortPair()
                            {
                                Action = SnortPair.GetActionByName(snortRule.Actions),
                                Key = con.Content,
                                RuleID = snortRule.Sid,
                                Field = -1,
                                Offset = Int32.Parse(con.Offset),
                                OffsetCount = iDepth - iLen + 1,
                                ConditionNum = snortRule.Conditions.Count
                            });

                            continue;
                        }
                    }

                    //Count Common condition
                    RulesInfo.CommonContentNum++;

                    RulesInfo.RulePairs.Add(new SnortPair()
                    {
                        Action = SnortPair.GetActionByName(snortRule.Actions),
                        Key = con.Content,
                        RuleID = snortRule.Sid,
                        Field = -1,
                        Offset = -1,
                        OffsetCount = 0,
                        ConditionNum = snortRule.Conditions.Count
                    });
                    
                    continue;

                }


                #endregion

                listRules.Add(snortRule);
            }

            return listRules;
        }

    }
}
