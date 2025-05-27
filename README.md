<h1>Suspend Roblox Threads</h1>
<h3>Allows you to suspend <b>all</b> threads on Roblox, allowing you to attach debuggers, disassemblers and memory scanners. This is useful if you are trying to reverse engineer Byfron (Roblox's anticheat) or trying to dump memory (for dumping scripts protected by Luarmor)</h3>

<h1>Installation</h1>
<ul>
  <li>Either build it yourself using the <a href="https://github.com/Aureliustics/Suspend-Roblox-Threads/blob/main/main.cpp" target="_blank">source code</a> in Visual Studio</li>
  <li>Or download the .exe from <a href="https://github.com/Aureliustics/Suspend-Roblox-Threads/releases/tag/Release" target="_blank">releases</a></li>
</ul>

<h1>Usage</h1>
<ul>
  <li>Run SuspendRobloxThreads.exe when Roblox is running</li>
  <li>Roblox should completely freeze if successful</li>
  <li>Attach whatever you like to Roblox (IDA, x64dbg, cheat engine)</li>
  <li>You won't get flagged because this also suspends Byfron threads</li>
</ul>

<h1>Use Case 1: Dump any Luarmor protected script (or any obfuscated script in general)</h1>
<ul>
  <li>1. Execute any obfuscated or protected script</li>
  <li>2. Run SuspendRobloxThreads.exe to freeze Roblox</li>
  <li>3. Open Cheat Engine</li>
  <li>4. Attach Cheat Engine to Roblox</li>
  <li>Search value type "string" and filter by "-- Bundled" then scan and copy the memory address where it's found</li>
  <li>Press Control + Alt + L in Cheat Engine to open lua cheat table</li>
  <li>Input the following code: readString(PLACEHOLDER, 888888, false) </li>
  <li>In the readString function replace "PLACEHOLDER" with the memory address you copied then run</li>
</ul>
