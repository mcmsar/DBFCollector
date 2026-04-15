//gsoap nsEMSBackupServer service name: BackupServer_WS
//gsoap nsEMSBackupServer service encoding:	literal
//gsoap nsEMSBackupServer service namespace: urn:tempuri
//gsoap nsEMSBackupServer schema  namespace: urn:nsEMSBackupServer

#import "soap12.h"
#import "ws-header.h"
#import "xop.h"
#import "xmlmime.h"

typedef wchar_t* xsd__string; 

//! A backup file attachment.
struct nsEMSBackupServer__BackupFile
{
	_xop__Include	xop__Include;
	xsd__string		wszSourcePath;
	@char*			xmlmime__contentType;
};

//! An array of backup attachements. Allows transmission of multiple attachments in one call.
struct nsEMSBackupServer__BackupFilesArray
{
	struct nsEMSBackupServer__BackupFile*	__ptr;
	int										__size;
};

//! An array of strings.
struct nsEMSBackupServer__StringArray
{
	xsd__string*	__ptr;
	int				__size;
};

struct nsEMSBackupServer__ULongArray
{
	unsigned long*	__ptr;
	int				__size;
};

//! A single manifest item record.
struct nsEMSBackupServer__ManifestItem
{
	unsigned long	ulManifestID;
	xsd__string		szSourcePath;
	unsigned long	ulFileSize;
	ULONG64			ui64BackupID;
};

//! An array of manifest items.
struct nsEMSBackupServer__ManifestItemArray
{
	struct nsEMSBackupServer__ManifestItem*	__ptr;
	int										__size;
};

//! Response to PutBackup.
struct nsEMSBackupServer__PutBackupResponse
{
	ULONG64										ui64BackupID;
	struct nsEMSBackupServer__ManifestItemArray aManifestItems;
};

//! Describes a backup ageout event.  The event type can be one of 0/NULL=none, 1=purge, 2=move offline
struct nsEMSBackupServer__AgeoutEvent
{
	short			sEventType;
	unsigned long	ulAgeoutDays;
};

//! An array of ageout events.
struct nsEMSBackupServer__AgeoutEventArray
{
	struct nsEMSBackupServer__AgeoutEvent*	__ptr;
	int										__size;
};

//! Describes a backup stored on the server.
struct nsEMSBackupServer__BackupDescription
{
	ULONG64	ui64BackupID;
	ULONG64 timeBackup;
	ULONG64 timeReceive;
	struct nsEMSBackupServer__AgeoutEventArray aAgeoutEvents;
};

//! An array of backup descriptions.
struct nsEMSBackupServer__BackupDescriptionArray
{
	struct nsEMSBackupServer__BackupDescription*	__ptr;
	int												__size;
};

//! Response to GetBackupList method.
struct nsEMSBackupServer__GetBackupListResponse
{
	struct nsEMSBackupServer__BackupDescriptionArray aBackups;
};

//! Response to GetAgeoutEvents method.
struct nsEMSBackupServer__GetAgeoutEventsResponse
{
	struct nsEMSBackupServer__AgeoutEventArray aAgeoutEvents;
};

//! Response to GetBackup method.
struct nsEMSBackupServer__GetBackupResponse
{
	struct nsEMSBackupServer__BackupFilesArray aBackupFiles;
};

//! Response to storage of agent audit record.
struct nsEMSBackupServer__AuditAgentConfigResponse
{
	ULONG64 ui64AuditID;
};

//! Send a set of backups as attachments and also provide information for cataloguing the backup.
int nsEMSBackupServer__PutBackup(	unsigned long ulSrcLutID,
									ULONG64 timeBackup,	// timestamp of backup creation on the agent.
									struct nsEMSBackupServer__BackupFilesArray aBackupFiles, 
									struct nsEMSBackupServer__AgeoutEventArray aAgeoutEvents,
									struct nsEMSBackupServer__PutBackupResponse& ret );

//! Get a list of backup descriptions for the given agent LUT ID.
int nsEMSBackupServer__GetBackupList(	unsigned long ulSrcLutID,
										struct nsEMSBackupServer__GetBackupListResponse& ret );

//! Get the ageout events for a particular backup.
int nsEMSBackupServer__GetAgeoutEvents( ULONG64 ui64BackupID, 
										struct nsEMSBackupServer__GetAgeoutEventsResponse& ret );

//! Set the ageout events for a particular backup.  Overrides any previous events.
int nsEMSBackupServer__PutAgeoutEvents( ULONG64 ui64BackupID,
										struct nsEMSBackupServer__AgeoutEventArray aAgeoutEvents,
										struct nsEMSBackupServer__PutAgeoutEventsResponse{}& ret );

//! Retrieve an entire or partial set of backup files by backup id and optionally list of manifest items.
//! If aManifestItems is empty then the entire backup set is returned.  Otherwise, only those files
//! listed in aManifestItems is returned.
int nsEMSBackupServer__GetBackup(	ULONG64 ui64BackupID, 
									struct nsEMSBackupServer__ULongArray aManifestItems,
									struct nsEMSBackupServer__GetBackupResponse& ret );

//! Store agent configuration.
int nsEMSBackupServer__AuditAgentConfig( unsigned long ulSrcLutID, ULONG64 timeAudit, xsd__string wszUser,
										xsd__string wszType, xsd__string wszConfiguration,
										struct nsEMSBackupServer__AuditAgentConfigResponse& ret );