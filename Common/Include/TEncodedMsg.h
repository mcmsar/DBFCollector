//---------------------------------------------------------------------------
#ifndef TEncodedMsgH
#define TEncodedMsgH
//---------------------------------------------------------------------------
#include <bitset>
#include "TBeaconMsg.h"

class _export TEncodedMsg
{
public:
    static const unsigned long NORMAL_FS = 0xFFFE2F;
    static const unsigned long INVERTED_FS = 0xFFFED0;

    TEncodedMsg();
    TEncodedMsg(const TBeaconMsg& Filter, const TBeaconMsg& Mask);
    ~TEncodedMsg();

    void SetPreamble(const unsigned long Type);
    void SetFormatFlag(const unsigned long FormatFlag);
    void SetProtocolFlag(const unsigned long ProtocolFlag);
    void SetCountryCode(const unsigned long CountryCode);
    void SetProtocolCode(const unsigned long ProtocolCode);
    void SetSerialCode(const unsigned long SerialCode);
    void SetHex15ID(TBeaconID& Hex15);

    void ClearPreamble(void);
    void ClearFormatFlag(void);
    void ClearProtocolFlag(void);
    void ClearCountryCode(void);
    void ClearProtocolCode(void);
    void ClearSerialCode(void);
    void ClearHex15ID(void);

    bool PreambleEncoded(void) const;
    bool FormatFlagEncoded(void) const;
    bool ProtocolFlagEncoded(void) const;
    bool CountryCodeEncoded(void) const;
    bool ProtocolCodeEncoded(void) const;
    bool SerialCodeEncoded(void) const;
    bool Hex15Encoded(void) const;

    bool IsUserProtocol(void) const;
    bool IsSerialUser(void) const;

    unsigned long Bits(const int Start, const int End) const;
    unsigned long MaskBits(const int Start, const int End) const;

    void Clear(void);

    TBeaconMsg Encode(void) const;
    TBeaconMsg EncodeMask(void) const;
    static TBeaconMsg Encode(const std::bitset<144>& BitPattern);

private:
    std::bitset<144> BeaconMessage;
    std::bitset<144> MessageMask;

    unsigned long Bits(const int Start, const int End,
        const std::bitset<144>& BitPattern) const;
};

#endif
