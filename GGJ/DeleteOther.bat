@echo off
if exist ".idea" rd /s /q ".idea" 2>nul
if exist ".vs" rd /s /q ".vs" 2>nul
if exist "Binaries" rd /s /q "Binaries" 2>nul
if exist "Intermediate" rd /s /q "Intermediate" 2>nul
if exist "DerivedDataCache" rd /s /q "DerivedDataCache" 2>nul
if exist "Saved" rd /s /q "Saved" 2>nul
if exist ".vsconfig" del /f /q ".vsconfig" 2>nul