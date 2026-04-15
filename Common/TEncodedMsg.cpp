//---------------------------------------------------------------------------
#include <vcl.h>
#include <bitset.h>
#pragma hdrstop

#include "TEncodedMsg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TEncodedMsg::TEncodedMsg()
{
}

TEncodedMsg::TEncodedMsg(const TBeaconMsg& Filter, const TBeaconMsg& Mask)
{
    for (int i = 0; i < 18; i++)
    {
        BeaconMessage <<= 8;
        MessageMask <<= 8;
        BeaconMessage |= (unsigned long)Filter.Message[i];
        MessageMask |= (unsigned long)Mask.Message[i];
    }
}

TEncodedMsg::~TEncodedMsg()
{
}

void TEncodedMsg::SetPreamble(const unsigned long Type)
{
    ClearPreamble();
    BeaconMessage |= std::bitset<144>(Type) << (144 - 24);
    MessageMask |= std::bitset<144>(0xFFFFFF) << (144 - 24);
}

void TEncodedMsg::SetFormatFlag(const unsigned long FormatFlag)
{
    ClearFormatFlag();
    BeaconMessage.set(144 - 25, FormatFlag);
    MessageMask.set(144 - 25);
}

void TEncodedMsg::SetProtocolFlag(const unsigned long ProtocolFlag)
{
    ClearProtocolFlag();
    BeaconMessage.set(144 - 26, ProtocolFlag);
    MessageMask.set(144 - 26);
}

void TEncodedMsg::SetCountryCode(const unsigned long CountryCode)
{
    ClearCountryCode();
    BeaconMessage |= std::bitset<144>(CountryCode) << (144 - 26 - 10);
    MessageMask |= std::bitset<144>(0x3FF) << (144 - 26 - 10);
}

void TEncodedMsg::SetProtocolCode(const unsigned long ProtocolCode)
{
    ClearProtocolCode();
    if (IsUserProtocol())
    {
        BeaconMessage |= std::bitset<144>(ProtocolCode) << (144 - 36 - 3);
        MessageMask |= std::bitset<144>(0x7) << (144 - 36 - 3);
    }
    else
    {
        BeaconMessage |= std::bitset<144>(ProtocolCode) << (144 - 36 - 4);
        MessageMask |= std::bitset<144>(0xF) << (144 - 36 - 4);
    }
}

void TEncodedMsg::SetSerialCode(const unsigned long SerialCode)
{
    ClearSerialCode();
    if (IsSerialUser())
    {
        BeaconMessage |= std::bitset<144>(SerialCode) << (144 - 39 - 3);
        MessageMask |= std::bitset<144>(0x7) << (144 - 39 - 3);
    }
}

void TEncodedMsg::SetHex15ID(TBeaconID& Hex15)
{
    std::bitset<144> Hex15Bits(*Hex15.High());

    ClearHex15ID();
    Hex15Bits <<= 32;
    Hex15Bits |= std::bitset<144>(*Hex15.Low());
    Hex15Bits <<= 144 - 25 - 60;
    BeaconMessage |= Hex15Bits;
    Hex15Bits.reset();
    Hex15Bits = 0x0FFFFFFF;
    Hex15Bits <<= 32;
    Hex15Bits |= 0xFFFFFFFF;
    Hex15Bits <<= 144 - 25 - 60;
    MessageMask |= Hex15Bits;
}

void TEncodedMsg::ClearPreamble(void)
{
    std::bitset<144> ClearMask =
        ~(std::bitset<144>(0xFFFFFF) << (144 - 24));

    BeaconMessage &= ClearMask;
    MessageMask &= ClearMask;
}

void TEncodedMsg::ClearFormatFlag(void)
{
    BeaconMessage.reset(144 - 25);
    MessageMask.reset(144 - 25);
}

void TEncodedMsg::ClearProtocolFlag(void)
{
    ClearProtocolCode();
    BeaconMessage.reset(144 - 26);
    MessageMask.reset(144 - 26);
}

void TEncodedMsg::ClearCountryCode(void)
{
    std::bitset<144> ClearMask =
        ~(std::bitset<144>(0x3FF) << (144 - 26 - 10));

    BeaconMessage &= ClearMask;
    MessageMask &= ClearMask;
}

void TEncodedMsg::ClearProtocolCode(void)
{
    std::bitset<144> ClearMask;

    if (IsUserProtocol())
    {
       ClearMask = ~(std::bitset<144>(0x7) << (144 - 36 - 3));
    }
    else
    {
       ClearMask = ~(std::bitset<144>(0xF) << (144 - 36 - 4));
    }

    ClearSerialCode();
    BeaconMessage &= ClearMask;
    MessageMask &= ClearMask;
}

void TEncodedMsg::ClearSerialCode(void)
{
    std::bitset<144> ClearMask =
        ~(std::bitset<144>(0x7) << (144 - 39 - 3));

    if (IsSerialUser())
    {
        BeaconMessage &= ClearMask;
        MessageMask   &= ClearMask;
    }
}

void TEncodedMsg::ClearHex15ID(void)
{
    for (int i = 144 - 25; i >= 144 - 85; i--)
    {
        BeaconMessage.reset(i);
    }
}

bool TEncodedMsg::PreambleEncoded(void) const
{
    return MaskBits(1, 24) == 0xFFFFFF;
}

bool TEncodedMsg::FormatFlagEncoded(void) const
{
    return MessageMask.test(144 - 25);
}

bool TEncodedMsg::ProtocolFlagEncoded(void) const
{
    return MessageMask.test(144 - 26);
}

bool TEncodedMsg::CountryCodeEncoded(void) const
{
    return MaskBits(27, 36) == 0x3FF;
}

bool TEncodedMsg::ProtocolCodeEncoded(void) const
{
    return IsUserProtocol() ? MaskBits(37, 39) == 0x7 :
        MaskBits(37, 40) == 0xF;
}

bool TEncodedMsg::SerialCodeEncoded(void) const
{
    return IsSerialUser() && MaskBits(40, 42) == 0x7;
}

bool TEncodedMsg::Hex15Encoded(void) const
{
    return MaskBits(26, 55) == 0x3FFFFFFF &&
        MaskBits(56, 85) == 0x3FFFFFFF;
}

bool TEncodedMsg::IsUserProtocol(void) const
{
    return BeaconMessage.test(144 - 26);
}

bool TEncodedMsg::IsSerialUser(void) const
{
    return IsUserProtocol() && Bits(37, 39) == BP_USR_SER;
}

unsigned long TEncodedMsg::Bits(const int Start, const int End) const
{
    return Bits(Start, End, BeaconMessage);
}

unsigned long TEncodedMsg::MaskBits(const int Start, const int End) const
{
    return Bits(Start, End, MessageMask);
}

void TEncodedMsg::Clear(void)
{
    BeaconMessage.reset();
    MessageMask.reset();
}

TBeaconMsg TEncodedMsg::Encode(void) const
{
    return Encode(BeaconMessage);
}

TBeaconMsg TEncodedMsg::EncodeMask(void) const
{
    return Encode(MessageMask);
}

unsigned long TEncodedMsg::Bits(const int Start, const int End,
    const std::bitset<144>& BitPattern) const
{
    unsigned long Value = 0;

    for (int i = 144 - Start; i >= 144 - End; i--)
    {
        Value <<= 1;

        if (BitPattern.test(i))
        {
            Value++;
        }
    }

    return Value;
}

TBeaconMsg TEncodedMsg::Encode(const std::bitset<144>& BitPattern)
{
    TBeaconMsg EncodedMessage;

    for (int i = 0; i < 18; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            EncodedMessage.Message[i] <<= 1;

            if (BitPattern.test(144 - i * 8 - j))
            {
                EncodedMessage.Message[i]++;
            }
        }
    }

    return EncodedMessage;
}

