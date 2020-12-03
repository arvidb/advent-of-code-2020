#!/bin/sh
cat helpers.swift $1 > tmp.swift
cat $2 | swift tmp.swift
rm tmp.swift
