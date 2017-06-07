using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace RuleAnalysis
{
    public partial class mainForm : Form
    {
        public mainForm()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void mainForm_Load(object sender, EventArgs e)
        {

        }

        private void txtRuleFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "*.rules|*.rules";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                txtRuleFile.Text = openFileDialog.FileName;
                string sFile = File.ReadAllText(openFileDialog.FileName);
                List<SnortRule> listRule = BLL.Transform(sFile);
                tbAllRules.Text = RulesInfo.RuleNum.ToString();
                tbTcpRules.Text = RulesInfo.TcpRuleNum.ToString();
                tbCommonPair.Text = RulesInfo.CommonContentNum.ToString();
                tbOffDepPair.Text = RulesInfo.OffsetDepthNum.ToString();
                tbFieldPair.Text = RulesInfo.HttpAttrNum.ToString();
                tbAllPair.Text = RulesInfo.AllPairNum.ToString();

            }
        }

        private void tbSavetoFile_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "*.pair|*.pair";
            List<string> arListString = new List<string>();
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                tbSavetoFile.Text = saveFileDialog.FileName;
                arListString.Add(RulesInfo.AllPairNum.ToString());
                foreach (SnortPair snortPair in RulesInfo.RulePairs)
                {
                    arListString.Add(snortPair.RuleID);
                    arListString.Add(snortPair.Action.ToString());
                    arListString.Add(snortPair.Field.ToString());
                    arListString.Add(snortPair.Offset.ToString());
                    arListString.Add(snortPair.OffsetCount.ToString());
                    arListString.Add(snortPair.ConditionNum.ToString());
                    arListString.Add(snortPair.Key);
                }
                File.WriteAllLines(saveFileDialog.FileName, arListString);
            }
        }
    }
}
