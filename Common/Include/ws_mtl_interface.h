//gsoap nsEMSMTLServer service name: MTL_WS
//gsoap nsEMSMTLServer service encoding:	literal
//gsoap nsEMSMTLServer service namespace: urn:tempuri
//gsoap nsEMSMTLServer schema  namespace: urn:nsEMSMTLServer

#import "WS-Header.h"

// gsoap generates the WSDL with all string fields as optional,
// change each string field that has 'minOccurs="0"' to 'minOccurs="1"' in order
// for WSDLToJava to be able to generate the proxy without errors (org.apache.cxf.tools.wsdlto.WSDLToJava)
// one of the errors is:
// java.lang.NoSuchMethodException: javax.xml.bind.annotation.XmlElementRef.required()
//     [java] 	at java.lang.Class.getDeclaredMethod(Unknown Source)
//     [java] 	at com.sun.codemodel.TypedAnnotationWriter.invoke(TypedAnnotationWriter.java:108)



typedef wchar_t* xsd__string; 

int nsEMSMTLServer__SendStatus( xsd__string szType, xsd__string szSource, 
							    xsd__string szStatus, xsd__string szStatusMsg, 
								struct nsEMSMTLServer__SendResponse{}& ret );

int nsEMSMTLServer__SendMsg( unsigned char szType, xsd__string szSource,
							 xsd__string szMsg, struct nsEMSMTLServer__SendMsgResponse{}& ret );
