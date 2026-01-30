# Root User Activity Playbook

## 1. Alert Overview
- **Severity:** Critical
- **Category:** Identity Abuse / Privileged Account Misuse
- **Data Source:** AWS CloudTrail
- **Trigger Condition:** Root account usage has been detected

## 2. Why This Alert Matters
Root account usage could indicate the highest level of compromise and potential damage.

## 3. Initial Triage (First 5 Minutes)
- Identify any related alerts (IAM Escalation, Login Attempts)
- Confirm source IP address and region
- Determine whether the usage is scheduled (i.e. billing) or unscheduled
- Check what actions have been taken by the user

## 4. Investigation Steps
### Review the triggering event
```sql
fields @timestamp, eventName, errorCode, userIdentity.userName, sourceIPAddress, userAgent
| filter userIdentity.type = "Root"
| sort @timestamp desc
```
## 5. False Positive Analysis

Possible benign causes:
- scheduled usage
- Emergency procedures

Validate:
- Confirm approval or change record
- Verify activity occurred within the approved window
- Ensure no unexpected follow-on actions occurred

## 6. Containment Actions
- Change Root Password
- Delete any root access keys
- Rotate/enable MFA
- Revoke any changes made by checking CloudTrail logs
- Restrict related IAM users if compromise is suspected

## 7. Eradication & Recovery
- Secure root email
- Review and revert any changes
- Use IAM roles for management purposes
- Ensure logging is on
- Force password reset if suspected compromise

## 8. Post-Incident Improvements
- use two person rule, no one has root password and mfa at one time
- Set up SNS notifications if not on for alerts
