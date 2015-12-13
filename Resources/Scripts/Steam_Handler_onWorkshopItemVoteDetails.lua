--------------------------------------------------------------------------------
--  Handler.......... : onWorkshopItemVoteDetails
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onWorkshopItemVoteDetails ( sItemID, nScore, nVotesFor, nVotesAgainst, nReports )
--------------------------------------------------------------------------------
	
	log.message ( "Vote details: \nItem: ", sItemID, "\nScore: ", nScore, "\nVotes+: ", nVotesFor, "\nVotes-: ", nVotesAgainst, "\nReports: ", nReports )
	--user.sendEvent ( this.getUser ( ), "MainMenuAI", "onItemVoteDetails", sItemID, nScore, nVotesFor, nVotesAgainst, nReports )
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
