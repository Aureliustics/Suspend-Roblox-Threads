<h1>Suspend Roblox Threads</h1>
<h3>Allows you to suspend <b>all</b> threads on Roblox and enabling debug privilege, allowing you to attach debuggers, disassemblers and memory scanners. This is useful if you are trying to reverse engineer Byfron (Roblox's anticheat) or trying to dump memory (for dumping scripts protected by Luarmor)</h3>

<h1>Installation</h1>
<ul>
  <li>Either build it yourself using the <a href="https://github.com/Aureliustics/Suspend-Roblox-Threads/blob/main/main.cpp" target="_blank">source code</a> in Visual Studio</li>
  <li>Or download the .exe from <a href="https://github.com/Aureliustics/Suspend-Roblox-Threads/releases/tag/Release" target="_blank">releases</a></li>
</ul>

<h1>Usage</h1>
<ul>
  <li>Run SuspendRobloxThreads.exe when Roblox is running</li>
  <li>Roblox should completely freeze if successful</li>
  <li>Attach whatever you like to Roblox (IDA, x64dbg, Cheat Engine)</li>
  <li>You won't get flagged because this also suspends Byfron threads</li>
</ul>

<h1>Use Case 1: Dump any Luarmor protected script (or any obfuscated script in general)</h1>
<ul>
  <li>1. Execute any obfuscated or protected script</li>
  <li>2. Run SuspendRobloxThreads.exe to freeze Roblox</li>
  <li>3. Open Cheat Engine and attach it to Roblox</li>
  <li>4. Search value type "string" and filter by "-- Bundled" or "getgenv" then scan and copy the memory address where it's found</li>
  <li>5. Press Control + Alt + L in Cheat Engine to open lua cheat table</li>
  <li>6. Input the following code: readString(PLACEHOLDER, 888888, false) </li>
  <li>7. In the readString function replace "PLACEHOLDER" with the memory address you copied then run</li>
</ul>
<p>Why does this work? Since the target script is loaded in memory, you are able to freeze Roblox, then attach a memory scanner (Cheat Engine) to search for the script's Lua code stored within Roblox with common comments and code (like --Bundled and getgenv)</p>
<p>We scan for the comment "-- Bundled" because it is the comment made when source code is compiled into 1 file with luabundle for exmaple: -- Bundled by luabundle {"luaVersion":"5.1","version":"1.6.0"}</p>
<p>We can also scan for getgenv because it is very common in scripts because it is the global envirornment of executors.</p>

<h1>Use Case 2: Reverse Engineering</h1>
<ul>
  <li>1. Run SuspendRobloxThreads.exe to freeze Roblox</li>
  <li>2. Since Byfron threads are suspended and debug privileges are enabled, you can attach anything you like without crashing and being flagged</li>
  <li>3. This allows you to analyze assembly pseudo code of Roblox freely</li>
</ul>
