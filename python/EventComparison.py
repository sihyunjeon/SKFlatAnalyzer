#!/usr/bin/env python

import os 
from os import listdir
from os.path import isfile,isdir, join    


# StringCounter: gets lists of txt files from PrintEvent function and renames it with a substring thats is the number of events in the list
def StringCounter(_dir):
    
    file_dir  = [f for f in listdir(_dir) if isfile(join(_dir,f))]
    for f in file_dir:
        
        name_f = f
        if 'DONE' in name_f:
            continue
        read_file = open(_dir+"/"+f ,"r")
        counter=0
        for line in read_file:
            counter=counter+1
        read_file.close()
        name_f = name_f.replace('.txt' ,'_nevents_' +str(counter)+'_DONE.txt')
        os.system('mv ' + _dir+'/'+f + ' ' + _dir+'/'+name_f)
        

# GetTimeStampFromList: Takes the array of event lists and substracts the timestamp from each list in order to make a unique multi timestamp string for SKimmed sample
def GetTimeStampFromList(Ev_list):
    ts_list=''
    for  list_path in Ev_list:
        mod_list_path = list_path.replace('/',' ')
        ts=mod_list_path.split()[5]
        ts_list+=ts+'_'
    ts_list_final = ts_list[:-1]
    return ts_list_final

# find_str: inputs a string and substring and returns the location of the substring 
def find_str(s, char):
    index = 0

    if char in s:
        c = char[0]
        for ch in s:
            if ch == c:
                if s[index:index+len(char)] == char:
                    return index

            index += 1

    return -1


# GetInfoFromList: Takes the event lists and extras the string identifier to the events (i.e. the SR name) to make skimmed sample dir 
def GetInfoFromList(Ev_list,sample):
    
    ts_list=''
    
    counter=0
    for  list_path in Ev_list:
        if not '.txt' in list_path:
            return ''
        if not sample in list_path:
            return ''

        counter+=1
        if counter > 2:
            continue
        mod_list_path = list_path.replace('/',' ')

        filename=mod_list_path.split()[6]
        n_sample_loc = find_str(filename, sample)
        filename=filename[0:n_sample_loc]

        ts_list+=filename
    ts_list_final = ts_list[:-1]
    return ts_list_final

    

# GetAllFilesFromDir: Takes the event list and if a dir is input not a txt file it lists all files in that directory 
def GetAllFilesFromDir(argEventLists,sample):

    if '.txt' in argEventLists:
        return argEventLists
    new_ev_list=''
    dir_list=[]
    if argEventLists != "":
        EventLists = (argEventLists).split(',')
        for l in EventLists:
            EventLists_mod = l.replace('/',' ')
            split_EventLists_mod='/'
            for x in range(0,len(EventLists_mod.split())):
                split_EventLists_mod+=EventLists_mod.split()[x]+"/"
            if not split_EventLists_mod in dir_list:
                dir_list.append(split_EventLists_mod)

    for _dir in dir_list:
        file_dir  = [f for f in listdir(_dir) if isfile(join(_dir,f))]
        for _file in file_dir:
            if sample in _file:
                new_ev_list+=_dir+"/"+_file+','
    
    new_ev_list=new_ev_list[:-1]
    
    return new_ev_list


# CheckListsAreSame: is a function to check if the lists used in EVlist are the same
def CheckListsAreSame(EventLists):
    
    import filecmp

    if len(EventLists) == 2:
        list1=EventLists[0]
        list2=EventLists[1]
        return filecmp.cmp(list1,list2)
    
    if len(EventLists) == 3:
        list1=EventLists[0]
        list2=EventLists[1]
        list3=EventLists[2]
        
        if filecmp.cmp(list1,list2) and filecmp.cmp(list1,list3) :
            return True
        else:
            return False
        
        
        
