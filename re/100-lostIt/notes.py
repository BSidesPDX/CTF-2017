#!/usr/bin/env python3

import datetime
import argparse
from sqlalchemy import Column, Integer, String, DateTime, MetaData
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy_utils import database_exists
from settings import DB
import uuid 

Base = declarative_base()

class VmList(Base):
    __tablename__ = 'secureNotes'
    ID = Column(Integer, unique=True, primary_key=True)
    dateAdded = Column(DateTime)
    notes = Column(String)
    password = Column(String)

def passwordHash(password, curTime):
    from Crypto.Cipher import DES3
    import base64
        
    key = str(curTime)
    key = key[0:16]
    iv = '12345678'
    passwordHash = DES3.new(key, DES3.MODE_CBC, iv)
    encryptedPassword = passwordHash.encrypt(password)
    return str(base64.b64encode(str(encryptedPassword).encode()))

def secretNotes(passwordHash, secretNote):
    return secretNote

# I forgot to save ! ! ! 
def viewNotes():
    return 


def addNote(password, secretNote):
    engine = create_engine(DB)
    meta = MetaData(engine, reflect=True)
    vmListing = meta.tables['secureNotes']
    conn = engine.connect()

    curTime = datetime.datetime.now()

    hashed = passwordHash(password, curTime)
    secret = secretNotes(hashed, secretNote)
    

    '''
    conn.execute(vmListing.insert(),[
    {'ID': uuid.uuid4(),
     'dateAdded': curTime,
     'notes': secret,
     'password': hashed
    }]) '''

if __name__ == "__main__":
    from sqlalchemy import create_engine
    if database_exists(DB):
        parser = argparse.ArgumentParser(description="My secret notes program")
        parser.add_argument('-p', '--password')
        parser.add_argument('-n', '--notes')
        args = parser.parse_args()

        if not args.password and  not args.notes:
            raise SystemExit("You need a password and a note")
            
        else:
            addNote(args.password, args.notes)        
    
    else:
        engine = create_engine(DB)
        Base.metadata.create_all(engine)

