import os

target = input("Enter the target IP: ")

os.system(f"shutdowm /s /m \\\\{target} /t 0")
