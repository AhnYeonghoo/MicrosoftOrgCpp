using HanaWPF.Control.Comm;
using HanaWPF.Control.Comm.Plc;
using HanaWPF.Data.Global.EnumLogs;
using SFACTInspector.Data.Command;
using SFACTInspector.Data.Global;
using SFACTInspector.Data.Global.EnumComm;
using SFACTInspector.Data.Table;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace SFACTInspector.Control.Comm.PLC
{
    public partial class PlcClient : BaseCommUnit
    {
        private MxComponent _mxComponent = null;

        private Stopwatch _swRxHeartBit = null;
        private Stopwatch _swTxHeartBit = null;
        private Stopwatch _swLoop = null;

        public List<PlcResult> PlcResults = new List<PlcResult>();
        public object LockPlcResult = new object();

        public PlcBlock RxBlockMap { get; set; } = null;
        public PlcBlock TxBlockMap { get; set; } = null;

        public PlcString RxRequestCellId { get; set; } = null;
        public PlcWord RxInterface { get; set; } = null;

        public PlcWord TxInterface { get; set; } = null;
        public PlcWordList TxCellResult { get; set; } = null;
        public PlcWordList TxMp1JrJudge { get; set; } = null;
        public PlcWordList TxMp2JrJudge { get; set; } = null;


        private bool _rxHeartBit = false;
        private bool RxHeartBit
        {
            set
            {
                if (_rxHeartBit == value)
                    return;

                _rxHeartBit = value;
                _swRxHeartBit.Restart();

                GUIMethod.Inspection.PlcRecvHeartBeat(_rxHeartBit);
            }
            get => _rxHeartBit;
        }

        private bool _txHeartBit = false;
        private bool TxHeartBit
        {
            set
            {
                if (_txHeartBit == value)
                    return;

                _txHeartBit = value;
                if (_txHeartBit)
                    GUIMethod.Inspection.PlcSendHeartBeat();
            }
        }


        private bool _rxInspReq = false;
        private bool RxInspReq
        {
            set
            {
                if (_rxInspReq == value)
                    return;

                _rxInspReq = value;

                if (_rxInspReq)
                {
                    GUIMethod.Inspection.SetPlcState(0);
                }
            }
            get => _rxInspReq;
        }

        private bool _txInspAck = false;
        private bool TxInspAck
        {
            set
            {
                if (_txInspAck == value)
                    return;

                _txInspAck = value;
                if (TxInspAck)
                    GUIMethod.Inspection.SetPlcState(1);
            }
            get => _txInspAck;
        }



        private int _retryTaskResultCount = 0;
        private int _mesFileCheckInterval = 0;

        public void Init()
        {
            _delayTime = 10;
            _mxComponent = new MxComponent();
            _mxComponent.LogicalNumber = 0;

            _swRxHeartBit = new Stopwatch();
            _swTxHeartBit = new Stopwatch();
            _swTxHeartBit.Start();

            _swLoop = new Stopwatch();
            _swLoop.Start();

            int rxAddress = SiteSettingTable.PlcRxAddress;
            int txAddress = SiteSettingTable.PlcTxAddress;

            if (GConfig.IsAppSimulation)
            {
                rxAddress -= 57000;
                txAddress -= 57000;
            }

            RxBlockMap = _mxComponent.CreateBlock(rxAddress, SiteSettingTable.PlcRxLength);
            TxBlockMap = _mxComponent.CreateBlock(txAddress, SiteSettingTable.PlcTxLength);

            RxInterface = _mxComponent.CreateWord(ConstPlcComm.INT_RX_INTERFACE_ADDR);
            TxInterface = _mxComponent.CreateWord(ConstPlcComm.INT_TX_INTERFACE_ADDR);

            RxRequestCellId = _mxComponent.CreateString(ConstPlcComm.INT_RX_REQCELLID_ADDR,