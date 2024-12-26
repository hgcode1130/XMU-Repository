DROP TABLE IF EXISTS [USERS];
CREATE TABLE [USERS]([rowid] INTEGER, [username] text, [passwd] text, [admin] int);

INSERT INTO [USERS]([rowid], [username], [passwd], [admin])
VALUES(1, 'admin', 'admin', 1);

