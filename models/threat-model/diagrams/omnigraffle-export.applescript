#!/usr/bin/osascript

-- OmniGraffle PDF Export
-- Daniel M. Zimmerman, February 2025

-- This AppleScript tells OmniGraffle to export the front document as a PDF,
-- with a number of border pixels specified by "borderPixels",
-- using the same base name that the document has; e.g., "x.graffle"
-- would export as "x.pdf"

-- Note that the document must already be open in OmniGraffle for this
-- to work; opening the document within the script seems to be
-- problematic in practice, so we use "open" in a prior step to open
-- the document. This script then closes the document, and quits OmniGraffle
-- if it no longer has any open documents.

tell application id "OGfl"
	set borderPixels to 10

	-- This repeat is necessary because sometimes the document opens slowly,
	-- and if it isn't open yet, the script will crash

	repeat until front document exists
	end repeat

	set graffleFile to front document
	set graffleFilePath to path of graffleFile

	-- Get filename without extension, and containing folder
	tell application "Finder"
		set {fileName, fileExtension, isHidden} to the ¬
			{displayed name, name extension, extension hidden} ¬
				of ((the graffleFilePath as POSIX file) as alias)
		set containingFolder to container of ((the graffleFilePath as POSIX file) as alias)
	end tell
	if (fileExtension ≠ missing value) then
		set baseName to texts 1 thru -((length of fileExtension) + 2) of fileName
	end if

	-- export the current canvas to a PNG in the same directory, with the
	-- same base name
	set currentCanvas to canvas of front window
	set outputFilePath to (containingFolder as string) & baseName & ".pdf" as string
	set area type of current export settings to current canvas
	set border amount of current export settings to borderPixels
	set include border of current export settings to true
	save graffleFile as "pdf" in file (outputFilePath)
	close front document
	set filepaths to the path of every document
	if length of filepaths is 0 then quit
end tell
